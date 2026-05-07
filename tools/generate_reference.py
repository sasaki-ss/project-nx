from __future__ import annotations

from reference.config import (
    ASSET_DIR,
    CSS_PATH,
    CSS_SOURCE_PATH,
    DECODE_CANDIDATES,
    EXCLUDED_SOURCE_TOP_DIRS,
    SITE_DIR,
    SOURCE_DIR,
    site_rel_from_source_rel,
)
from reference.renderer import read_markdown, render_page
from reference.sidebar import build_sidebar, build_tree, rel_href


def write_css() -> None:
    ASSET_DIR.mkdir(parents=True, exist_ok=True)
    CSS_PATH.write_text(CSS_SOURCE_PATH.read_text(encoding="utf-8"), encoding="utf-8")


def main() -> None:
    SITE_DIR.mkdir(parents=True, exist_ok=True)
    write_css()
    tree = build_tree()

    for md in SOURCE_DIR.rglob("*.md"):
        rel = md.relative_to(SOURCE_DIR)
        if rel.parts and rel.parts[0] in EXCLUDED_SOURCE_TOP_DIRS:
            continue
        target = SITE_DIR / site_rel_from_source_rel(rel)
        target.parent.mkdir(parents=True, exist_ok=True)

        sidebar_html = build_sidebar(tree, rel)
        md_text = read_markdown(md, DECODE_CANDIDATES)
        html_text = render_page(md_text, rel, sidebar_html, rel_href_fn=rel_href)

        target.write_text(html_text, encoding="utf-8")
        print(f"generated: {target}")


if __name__ == "__main__":
    main()
