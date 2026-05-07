from __future__ import annotations

import html
import re
from pathlib import Path

from .config import CPP_KEYWORDS, SECTION_CHIP_MAP, SOURCE_DIR, site_rel_from_source_rel


def read_markdown(path: Path, decode_candidates: tuple[str, ...]) -> str:
    raw = path.read_bytes()
    if raw.startswith(b"\xef\xbb\xbf"):
        return raw.decode("utf-8-sig")
    if raw.startswith(b"\xff\xfe") or raw.startswith(b"\xfe\xff"):
        return raw.decode("utf-16")
    for enc in decode_candidates:
        try:
            return raw.decode(enc)
        except UnicodeDecodeError:
            continue
    return raw.decode("utf-8", errors="replace")


def inline_md(text: str) -> str:
    text = html.escape(text)
    text = re.sub(r"`([^`]+)`", r"<code>\1</code>", text)
    text = re.sub(r"\[([^\]]+)\]\(([^)]+)\)", r'<a href="\2">\1</a>', text)
    return text


def highlight_cpp(code: str) -> str:
    esc = html.escape(code)
    esc = re.sub(r"(//.*)$", r'<span class="tok-com">\1</span>', esc, flags=re.MULTILINE)
    esc = re.sub(r'(&quot;.*?&quot;)', r'<span class="tok-str">\1</span>', esc)
    esc = re.sub(r"\b(\d+)\b", r'<span class="tok-num">\1</span>', esc)

    def kw_sub(m: re.Match[str]) -> str:
        word = m.group(0)
        if word in {"include", "std"}:
            return f'<span class="tok-pre">{word}</span>'
        if word in {"int", "bool", "float", "double", "char", "void", "auto"}:
            return f'<span class="tok-type">{word}</span>'
        return f'<span class="tok-kw">{word}</span>'

    pattern = r"\b(" + "|".join(sorted(CPP_KEYWORDS, key=len, reverse=True)) + r")\b"
    parts = re.split(r"(<[^>]+>)", esc)
    for i, part in enumerate(parts):
        if i % 2 == 0:
            parts[i] = re.sub(pattern, kw_sub, part)
    return "".join(parts)


def convert_body(md: str) -> str:
    lines = md.splitlines()
    out: list[str] = []
    in_code = False
    code_lang = ""
    code_buf: list[str] = []
    in_table = False
    in_list = False
    first_table_row = False

    for line in lines:
        s = line.rstrip()
        if s.strip().startswith("<!--") and s.strip().endswith("-->"):
            continue

        if s.startswith("```"):
            if not in_code:
                code_lang = s[3:].strip().lower()
                code_buf = []
                in_code = True
            else:
                lang_name = code_lang if code_lang else ""
                klass = f' class="language-{lang_name}"' if lang_name else ""
                raw = "\n".join(code_buf)
                if code_lang in {"cpp", "c++", "cc", "cxx", "hpp", "h"}:
                    rendered = highlight_cpp(raw)
                else:
                    rendered = html.escape(raw)
                out.append(f"<pre><code{klass}>{rendered}</code></pre>")
                in_code = False
            continue

        if in_code:
            code_buf.append(line)
            continue

        if s.startswith("#"):
            if in_list:
                out.append("</ul>")
                in_list = False
            if in_table:
                out.append("</table>")
                in_table = False
            level = len(s) - len(s.lstrip("#"))
            text = s[level:].strip()
            if level == 2 and text in SECTION_CHIP_MAP:
                chip_kind = SECTION_CHIP_MAP[text]
                out.append(f'<h2 class="section-chip section-chip-{chip_kind}">{inline_md(text)}</h2>')
            else:
                out.append(f"<h{level}>{inline_md(text)}</h{level}>")
            continue

        if s.startswith("|") and s.endswith("|"):
            if not in_table:
                out.append("<table>")
                in_table = True
                first_table_row = True
            cells = [c.strip() for c in s.strip("|").split("|")]
            if all(re.fullmatch(r"-+", c.replace(" ", "")) for c in cells):
                continue
            tag = "th" if first_table_row else "td"
            row = "".join(f"<{tag}>{inline_md(c)}</{tag}>" for c in cells)
            out.append(f"<tr>{row}</tr>")
            first_table_row = False
            continue
        elif in_table:
            out.append("</table>")
            in_table = False

        if s.startswith("- "):
            if not in_list:
                out.append("<ul>")
                in_list = True
            out.append(f"<li>{inline_md(s[2:].strip())}</li>")
            continue
        elif in_list:
            out.append("</ul>")
            in_list = False

        out.append(f"<p>{inline_md(s)}</p>" if s else "")

    if in_table:
        out.append("</table>")
    if in_list:
        out.append("</ul>")

    return "\n".join(out)


def strip_section(md_text: str, section_name: str) -> str:
    lines = md_text.splitlines()
    out: list[str] = []
    i = 0
    in_target = False
    target = f"## {section_name}"

    while i < len(lines):
        line = lines[i]
        if line.strip() == target:
            in_target = True
            i += 1
            continue
        if in_target and line.startswith("## "):
            in_target = False
        if not in_target:
            out.append(line)
        i += 1
    return "\n".join(out)


def simplify_related_item_labels(md_text: str) -> str:
    lines = md_text.splitlines()
    out: list[str] = []
    in_related = False

    for line in lines:
        s = line.strip()
        if s == "## 関連項目":
            in_related = True
            out.append(line)
            continue
        if in_related and s.startswith("## "):
            in_related = False

        if in_related:
            def repl(m: re.Match[str]) -> str:
                label = m.group(1)
                href = m.group(2)
                short = label.rsplit("::", 1)[-1]
                return f"[{short}]({href})"
            line = re.sub(r"\[([^\]]*::[^\]]+)\]\(([^)]+)\)", repl, line)

        out.append(line)

    return "\n".join(out)


def parse_h2_sections(md_text: str) -> dict[str, str]:
    sections: dict[str, list[str]] = {}
    current: str | None = None
    for line in md_text.splitlines():
        s = line.rstrip()
        if s.startswith("## "):
            current = s[3:].strip()
            sections.setdefault(current, [])
            continue
        if current is not None:
            sections[current].append(line)
    return {k: "\n".join(v).strip() for k, v in sections.items()}


def extract_signature_code(sections: dict[str, str]) -> str:
    raw = sections.get("シグネチャ", "")
    if not raw:
        return ""
    m = re.search(r"```(?:cpp|c\+\+)?\s*(.*?)```", raw, re.DOTALL | re.IGNORECASE)
    if not m:
        return ""
    return m.group(1).strip()


def infer_function_section(title: str, signature: str, section_name: str) -> str:
    func = title.split("::")[-1]
    in_dxlib = "DxLibInput" in title

    if section_name == "戻り値":
        if func in {"ctor", "dtor", "update"} or signature.startswith("void "):
            return "なし"
        if func == "init":
            return "`true` なら初期化成功、`false` なら失敗です。"
        if func == "set_input_source":
            return "`true` なら設定成功、`false` なら失敗です。"
        if func.startswith("get_input") or func in {"get_key_state", "get_mouse_state"}:
            return "`true` なら指定入力が指定状態です。"
        if func == "get_mouse_point":
            if "optional" in signature:
                return "座標取得可能時は値を返し、不可時は `std::nullopt` を返します。"
            return "現在のマウス座標参照を返します。"
        return ""

    if section_name == "計算量":
        if func in {"init", "update"}:
            return "実装依存（1フレーム分の更新/初期化コストに依存）"
        return "O(1)"

    if section_name == "例外":
        if in_dxlib:
            return "DxLib 呼び出しに起因する失敗が起こりえます。"
        return "投げない想定（実装依存）"

    if section_name == "備考":
        if func in {"ctor"}:
            return "初期状態を構築します。"
        if func in {"dtor"}:
            return "保持リソースを解放します。"
        if func == "update":
            return "通常はフレームごとに呼び出します。"
        if func == "init":
            return "利用開始前に呼び出します。"
        if func.startswith("get_"):
            return "`update()` 呼び出し後の最新状態を参照します。"
        if func == "set_input_source":
            return "入力ソース差し替え時に呼び出します。"
        return ""

    return ""


def render_function_body(md_text: str) -> str:
    sections = parse_h2_sections(md_text)
    signature = extract_signature_code(sections)
    title = page_title(md_text, "")

    parts: list[str] = []
    if signature:
        parts.append(f'<pre class="top-definition"><code class="language-cpp">{highlight_cpp(signature)}</code></pre>')

    ordered = ["概要", "戻り値", "計算量", "例外", "備考", "サンプルコード"]
    rendered: set[str] = set()
    for name in ordered:
        body = sections.get(name, "").strip()
        if not body and name in {"戻り値", "計算量", "例外", "備考"}:
            body = infer_function_section(title, signature, name).strip()
        if not body:
            continue
        parts.append(f"<h2>{inline_md(name)}</h2>")
        parts.append(convert_body(body))
        rendered.add(name)

    # Render any additional h2 sections in source order after the standard blocks.
    for name, body in sections.items():
        if name in rendered or name == "シグネチャ":
            continue
        body = body.strip()
        if not body:
            continue
        parts.append(f"<h2>{inline_md(name)}</h2>")
        parts.append(convert_body(body))
    return "\n".join(parts)


def extract_definition_block(md_text: str) -> str:
    pattern = re.compile(r"^##\s+定義\s*$", re.MULTILINE)
    m = pattern.search(md_text)
    if not m:
        return ""
    tail = md_text[m.end():]
    code = re.search(r"```(?:[^\n]*)\n(.*?)\n```", tail, re.DOTALL)
    if not code:
        return ""
    body = highlight_cpp(code.group(1))
    return f'<pre class="top-definition"><code class="language-cpp">{body}</code></pre>'


def extract_header_include(md_text: str) -> str:
    inc = re.search(r"#\s*include\s*[<\"][^>\"]+[>\"]", md_text)
    return inc.group(0).strip() if inc else ""


def has_sample_section(md_text: str) -> bool:
    return re.search(r"^\s*##\s+サンプルコード\s*$", md_text, re.MULTILINE) is not None


def extract_category_override(md_text: str) -> str:
    m = re.search(r"<!--\s*@category:\s*([a-zA-Z0-9 _-]+)\s*-->", md_text)
    if not m:
        return ""
    raw = m.group(1).strip().lower()
    allowed = {"class", "struct", "enum class", "interface", "function", "type", "category", "reference", "header"}
    return raw if raw in allowed else ""


def page_title(md_text: str, fallback: str) -> str:
    for line in md_text.splitlines():
        s = line.strip()
        if s.startswith("# "):
            return s[2:].strip()
    return fallback


def is_function_page(rel_md: Path) -> bool:
    if len(rel_md.parts) < 3:
        return False
    parent = rel_md.parent
    class_md = parent.parent / f"{parent.name}.md"
    function_group_index = parent / "index.md"
    return (
        class_md != rel_md
        and (SOURCE_DIR / class_md).exists()
        and (SOURCE_DIR / function_group_index).exists()
    )


def detect_category(md_text: str, rel_md: Path) -> str:
    override = extract_category_override(md_text)
    if override:
        return override

    if rel_md.name == "index.md":
        return "reference" if rel_md == Path("index.md") else "category"
    if is_function_page(rel_md):
        return "function"

    lower = md_text.lower()
    if "enum class " in lower:
        return "enum class"
    if "struct " in lower:
        return "struct"
    if "class " in lower:
        class_name = rel_md.stem
        if class_name.startswith("I") or "= 0;" in md_text:
            return "interface"
        return "class"
    return "type"


def category_class(category: str) -> str:
    token = re.sub(r"[^a-z0-9]+", "-", category.lower()).strip("-")
    return f"api-category-{token}" if token else "api-category-type"


def render_title_block(title: str, category: str) -> str:
    if category == "header":
        short = title.rsplit("::", 1)[-1] if "::" in title else title
        h1 = f'<h1 class="api-title"><span class="title-name">{html.escape(short)}</span></h1>'
        cklass = category_class(category)
        return f'<div class="api-category {cklass}">{html.escape(category)}</div>{h1}'

    if "::" in title:
        ns, name = title.rsplit("::", 1)
        ns_html = html.escape(ns + "::")
        name_html = html.escape(name)
        h1 = f'<h1 class="api-title"><span class="title-namespace">{ns_html}</span><span class="title-name">{name_html}</span></h1>'
    else:
        h1 = f'<h1 class="api-title"><span class="title-name">{html.escape(title)}</span></h1>'
    cklass = category_class(category)
    return f'<div class="api-category {cklass}">{html.escape(category)}</div>{h1}'


def render_auto_sample_block(title: str, category: str, include_line: str) -> str:
    if not include_line:
        return ""

    parts = title.split("::")
    short_name = parts[-1]
    qualified_ns = "::".join(parts[:-1])
    type_qualified = f"{qualified_ns}::{short_name}" if qualified_ns else short_name
    using_line = f"using {type_qualified};" if qualified_ns else ""
    include_text = include_line

    if category in {"class", "struct", "interface", "type"}:
        body = [
            include_text,
            "",
            using_line if using_line else "",
            "",
            "int main() {",
            f"    {short_name} value{{}};",
            "    (void)value;",
            "    return 0;",
            "}",
        ]
        sample = "\n".join(line for line in body if line != "")
    elif category == "enum class":
        body = [
            include_text,
            "",
            using_line if using_line else "",
            "",
            "int main() {",
            f"    // {short_name} の値を選択して状態を扱う",
            f"    auto state = {short_name}::Pressed;",
            "    (void)state;",
            "    return 0;",
            "}",
        ]
        sample = "\n".join(line for line in body if line != "")
    elif category == "function":
        owner = parts[-2] if len(parts) >= 2 else "Target"
        owner_qualified = "::".join(parts[:-1]) if len(parts) >= 2 else owner
        owner_using = f"using {owner_qualified};" if "::" in owner_qualified else ""
        body = [
            include_text,
            "",
            owner_using if owner_using else "",
            "",
            "int main() {",
            f"    {owner} target{{}};",
            f"    // {short_name} を呼び出す",
            f"    target.{short_name}();",
            "    return 0;",
            "}",
        ]
        sample = "\n".join(line for line in body if line != "")
    else:
        return ""

    rendered = highlight_cpp(sample)
    return (
        "<h2>サンプルコード</h2>"
        f"<pre><code class=\"language-cpp\">{rendered}</code></pre>"
    )


def layer_path(rel_md: Path) -> str:
    return "root" if rel_md.parent == Path(".") else rel_md.parent.as_posix()


def is_root_index(rel_md: Path) -> bool:
    return rel_md == Path("index.md")


def is_directory_index(rel_md: Path) -> bool:
    return rel_md.name == "index.md" and not is_root_index(rel_md)


def rewrite_links(content_html: str, current_md: Path, rel_href_fn) -> str:
    pattern = re.compile(r'href="([^"]+)"')

    def replace(m: re.Match[str]) -> str:
        href = m.group(1)
        current_html = site_rel_from_source_rel(current_md)

        if "docs/reference/source/" in href:
            idx = href.find("docs/reference/source/")
            source_rel = Path(href[idx + len("docs/reference/source/"):])
            target = site_rel_from_source_rel(source_rel)
            return f'href="{rel_href_fn(current_html, target)}"'

        if href.endswith(".md"):
            source_rel = Path(href)
            target = site_rel_from_source_rel(source_rel)
            return f'href="{str(target.as_posix())}"'

        return m.group(0)

    return pattern.sub(replace, content_html)


def render_page(md_text: str, rel_md: Path, sidebar_html: str, rel_href_fn) -> str:
    md_text = simplify_related_item_labels(md_text)
    definition_block = extract_definition_block(md_text)
    category = detect_category(md_text, rel_md)
    include_line = extract_header_include(md_text)
    clean_md = strip_section(strip_section(strip_section(md_text, "定義"), "所属レイヤー"), "ヘッダ")
    if category == "function":
        definition_block = ""
        body_html = rewrite_links(render_function_body(md_text), rel_md, rel_href_fn)
    else:
        body_html = rewrite_links(convert_body(clean_md), rel_md, rel_href_fn)
        body_html = re.sub(r"^\s*<h1>.*?</h1>\s*", "", body_html, count=1, flags=re.DOTALL)
        body_html = re.sub(r"<h2>ヘッダ</h2>\s*<pre>.*?</pre>\s*", "", body_html, flags=re.DOTALL)
        if include_line and not has_sample_section(md_text):
            body_html += render_auto_sample_block(page_title(md_text, rel_md.stem), category, include_line)

    rel_html = site_rel_from_source_rel(rel_md)
    css_href = rel_href_fn(rel_html, Path("assets/reference.css"))
    raw_title = page_title(md_text, rel_md.stem)
    title = html.escape(raw_title)
    title_block = render_title_block(raw_title, category)
    layer = html.escape(layer_path(rel_md))

    if is_root_index(rel_md):
        title_block = f'<h1 class="api-title"><span class="title-name">{html.escape(raw_title)}</span></h1>'
        layer = ""
    elif is_directory_index(rel_md):
        title_block = f'<h1 class="api-title"><span class="title-name">{html.escape(raw_title)}</span></h1>'

    return f"""<!doctype html>
<html lang=\"ja\">
<head>
  <meta charset=\"utf-8\" />
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />
  <title>{title} - NX Reference</title>
  <link rel=\"stylesheet\" href=\"{css_href}\" />
</head>
<body>
  <div class=\"layout\">{sidebar_html}<main class=\"content\">{f'<div class="api-layer">{layer}</div>' if layer else ''}{title_block}{definition_block}{body_html}</main></div>
  <script>
  (function () {{
    const root = document.documentElement;
    const btn = document.getElementById('theme-toggle');
    const key = 'nx_reference_theme';
    const saved = localStorage.getItem(key);
    const prefersDark = window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches;
    const initial = saved || (prefersDark ? 'dark' : 'light');
    root.setAttribute('data-theme', initial);
    if (btn) btn.textContent = initial === 'dark' ? 'Light' : 'Dark';
    if (btn) btn.addEventListener('click', function () {{
      const current = root.getAttribute('data-theme') === 'dark' ? 'dark' : 'light';
      const next = current === 'dark' ? 'light' : 'dark';
      root.setAttribute('data-theme', next);
      localStorage.setItem(key, next);
      btn.textContent = next === 'dark' ? 'Light' : 'Dark';
    }});
  }})();
  </script>
</body>
</html>
"""
