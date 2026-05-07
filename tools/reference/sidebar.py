from __future__ import annotations

import html
import re
from dataclasses import dataclass, field
from functools import lru_cache
from pathlib import Path

from .config import EXCLUDED_SOURCE_TOP_DIRS, INPUTSTATE_GROUP_STEMS, NAV_TOP_ORDER, SOURCE_DIR, site_rel_from_source_rel


@dataclass
class NavNode:
    name: str
    path: Path
    index_md: Path | None = None
    files: list[Path] = field(default_factory=list)
    children: dict[str, "NavNode"] = field(default_factory=dict)


def rel_href(from_rel_html: Path, to_rel_html: Path) -> str:
    from_dir = from_rel_html.parent
    up = [".."] * len(from_dir.parts)
    base = Path(*up) if up else Path(".")
    return str((base / to_rel_html).as_posix())


def build_tree() -> NavNode:
    root = NavNode(name="NX Reference", path=Path("."))
    for md in sorted(SOURCE_DIR.rglob("*.md")):
        rel = md.relative_to(SOURCE_DIR)
        if rel.parts and rel.parts[0] in EXCLUDED_SOURCE_TOP_DIRS:
            continue
        cur = root
        for part in rel.parts[:-1]:
            if part not in cur.children:
                child_path = cur.path / part if cur.path != Path(".") else Path(part)
                cur.children[part] = NavNode(name=part, path=child_path)
            cur = cur.children[part]

        if rel.name == "index.md":
            cur.index_md = rel
        else:
            cur.files.append(rel)

    return root


def label_for_dir(name: str, depth: int) -> str:
    if depth == 0 and name.lower() in NAV_TOP_ORDER:
        return name.capitalize()
    return name


def display_name(stem: str) -> str:
    if stem == "ctor":
        return "(constructor)"
    if stem == "dtor":
        return "(destructor)"
    return stem


def namespace_for_path(path: Path) -> str:
    parts = list(path.parts)
    if not parts:
        return ""
    if parts[0] == "core":
        if len(parts) == 1:
            return "nx::core"
        return "nx::" + "::".join(parts)
    if parts[0] == "adapter":
        return "::".join(parts)
    return "::".join(parts)


@lru_cache(maxsize=512)
def namespace_for_md(rel_md: Path) -> str:
    abs_md = SOURCE_DIR / rel_md
    if not abs_md.exists():
        return namespace_for_path(rel_md.parent)

    try:
        for line in abs_md.read_text(encoding="utf-8").splitlines():
            s = line.strip().lstrip("\ufeff")
            if s.startswith("# "):
                title = s[2:].strip()
                if "::" in title:
                    return title.rsplit("::", 1)[0]
                return ""
    except UnicodeDecodeError:
        pass
    return namespace_for_path(rel_md.parent)


@lru_cache(maxsize=512)
def category_for_md(rel_md: Path) -> str:
    abs_md = SOURCE_DIR / rel_md
    if not abs_md.exists():
        return ""
    try:
        text = abs_md.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        return ""
    m = html.unescape(text)
    # Markdown metadata override: <!-- @category: ... -->
    hit = re.search(r"<!--\s*@category:\s*([a-zA-Z0-9 _-]+)\s*-->", m)
    return hit.group(1).strip().lower() if hit else ""


def render_class_like_label(stem: str, parent_path: Path, rel_md: Path | None = None) -> str:
    if rel_md is not None and category_for_md(rel_md) == "header":
        return html.escape(stem)
    ns = namespace_for_md(rel_md) if rel_md is not None else namespace_for_path(parent_path)
    if not ns:
        return html.escape(stem)
    return f'<span class="sidebar-namespace">{html.escape(ns)}::</span><span class="sidebar-symbol">{html.escape(stem)}</span>'


def is_type_like_name(stem: str) -> bool:
    if not stem:
        return False
    if stem in {"ctor", "dtor"}:
        return False
    return stem[0].isupper()


def node_contains_current(node: NavNode, current_md: Path) -> bool:
    if node.index_md == current_md:
        return True
    if any(f == current_md for f in node.files):
        return True
    return any(node_contains_current(c, current_md) for c in node.children.values())


def remap_children_for_display(node: NavNode) -> tuple[list[Path], dict[str, NavNode]]:
    files = list(node.files)
    children = dict(node.children)

    if node.path.as_posix() == "core/input":
        grouped_stems = INPUTSTATE_GROUP_STEMS
        grouped_files = [f for f in files if f.stem in grouped_stems]
        if grouped_files:
            files = [f for f in files if f.stem not in grouped_stems]
            synthetic = children.get("InputState")
            if synthetic is None:
                synthetic = NavNode(name="InputState", path=node.path / "InputState")
            existing = {f.as_posix() for f in synthetic.files}
            for f in grouped_files:
                if f.as_posix() not in existing:
                    synthetic.files.append(f)
            synthetic.files.sort(key=lambda p: p.stem.lower())
            children["InputState"] = synthetic

    return files, children


def render_dir(node: NavNode, current_md: Path, current_html: Path, depth: int = 0) -> str:
    parts: list[str] = []
    consumed_children: set[str] = set()
    node_files, node_children = remap_children_for_display(node)
    # Enable file-unit rendering only where class/type page and same-name function directory coexist.
    file_unit_mode = any(f.stem in node_children for f in node_files)

    for sub in sorted(node_files, key=lambda p: p.stem.lower()):
        child = node_children.get(sub.stem)
        href = rel_href(current_html, site_rel_from_source_rel(sub))
        active = " class=\"active\"" if sub == current_md else ""
        # Present module entries as file units (e.g. InputSystem.h) only at module level.
        if file_unit_mode:
            head_label = render_class_like_label(sub.stem, node.path, sub)
            head = f'<a href="{href}"{active}>{head_label}</a>'
        else:
            head = f'<a href="{href}"{active}>{html.escape(display_name(sub.stem))}</a>'

        if child is None:
            if not file_unit_mode and is_type_like_name(sub.stem):
                ns_head = (
                    f'<a href="{href}"{active}>{render_class_like_label(sub.stem, node.path, sub)}</a>'
                )
                parts.append(f"<li>{ns_head}</li>")
            else:
                parts.append(f"<li>{head}</li>")
            continue

        consumed_children.add(sub.stem)
        sub_parts: list[str] = []

        nested = render_dir(child, current_md, current_html, depth + 1)
        if nested:
            sub_parts.append(nested)

        child_has_current = node_contains_current(child, current_md) or sub == current_md
        open_attr = " open" if child_has_current else ""
        branch_class = ' class="current-branch"' if child_has_current else ""
        parts.append(f"<li><details{open_attr}{branch_class}><summary>{head}</summary><ul>{''.join(sub_parts)}</ul></details></li>")

    for key in sorted(node_children.keys(), key=lambda x: (x.lower() not in NAV_TOP_ORDER, x.lower())):
        if key in consumed_children:
            continue
        child = node_children[key]
        label = html.escape(label_for_dir(child.name, depth))
        if child.index_md:
            href = rel_href(current_html, site_rel_from_source_rel(child.index_md))
            active = " class=\"active\"" if child.index_md == current_md else ""
            head = f'<a href="{href}"{active}>{label}</a>'
        else:
            head = label

        sub_parts: list[str] = []
        sub_dirs = render_dir(child, current_md, current_html, depth + 1)
        if sub_dirs:
            sub_parts.append(sub_dirs)

        if sub_parts:
            child_has_current = node_contains_current(child, current_md)
            open_attr = " open" if child_has_current else ""
            branch_class = ' class="current-branch"' if child_has_current else ""
            parts.append(f"<li><details{open_attr}{branch_class}><summary>{head}</summary><ul>{''.join(sub_parts)}</ul></details></li>")
        else:
            parts.append(f"<li>{head}</li>")

    return "".join(parts)


def build_sidebar(root: NavNode, current_md: Path) -> str:
    current_html = site_rel_from_source_rel(current_md)
    top_href = rel_href(current_html, Path("index.html"))
    top_active = " class=\"active\"" if current_md == Path("index.md") else ""
    tree_html = render_dir(root, current_md, current_html)

    return (
        '<aside class="sidebar">'
        '<div class="sidebar-header">'
        f'<div class="sidebar-title"><a href="{top_href}"{top_active}>NX Reference</a></div>'
        '<button id="theme-toggle" class="theme-toggle" type="button">Dark</button>'
        '</div>'
        '<nav class="sidebar-nav">'
        f'<ul>{tree_html}</ul>'
        '</nav>'
        '</aside>'
    )
