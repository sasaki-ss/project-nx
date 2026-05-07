from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SOURCE_DIR = ROOT / "docs" / "reference" / "source"
SITE_DIR = ROOT / "docs" / "reference" / "site"
ASSET_DIR = SITE_DIR / "assets"
CSS_PATH = ASSET_DIR / "reference.css"
CSS_SOURCE_PATH = ROOT / "tools" / "reference" / "reference.css"

DECODE_CANDIDATES = ("utf-8", "cp932")
NAV_TOP_ORDER = {"core", "adapter", "app"}
EXCLUDED_SOURCE_TOP_DIRS = {"_templates"}
INPUTSTATE_GROUP_STEMS = {"Key", "Mouse", "MousePoint", "KeyHash", "MouseHash"}
SECTION_CHIP_MAP = {
    "クラス": "class",
    "列挙型": "enum",
    "構造体・補助型": "struct",
}

CPP_KEYWORDS = {
    "class", "struct", "enum", "namespace", "public", "private", "protected", "virtual",
    "override", "final", "const", "constexpr", "static", "inline", "template", "typename",
    "using", "return", "if", "else", "for", "while", "switch", "case", "default", "auto",
    "noexcept", "void", "bool", "int", "float", "double", "char", "unsigned", "signed",
    "true", "false", "nullptr", "include", "std",
}


def site_rel_from_source_rel(rel_md: Path) -> Path:
    # Group InputState-related types under core/input/InputState in generated site.
    if rel_md.parts[:2] == ("core", "input") and len(rel_md.parts) == 3:
        stem = rel_md.stem
        if stem in INPUTSTATE_GROUP_STEMS:
            return Path("core") / "input" / "InputState" / f"{stem}.html"
    return rel_md.with_suffix(".html")
