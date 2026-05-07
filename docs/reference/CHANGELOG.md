# NX Reference Changelog

## 2026-05-07 (Initial Baseline + Sidebar/Function Layout Iteration)

この時点はワークツリーが未追跡ファイル中心のため、`git diff --name-only` では差分が列挙されませんでした。  
そのため、本履歴は「現時点で存在する生成・正本・生成スクリプトのファイル群」を対応範囲として記録します。

### 対応範囲（ディレクトリ）

- `docs/reference/source/`
- `docs/reference/site/`
- `tools/generate_reference.py`
- `tools/reference/`

### 主要対応内容

- APIリファレンス基盤の作成（`source` 正本 / `site` 生成物）
- サイドバー付き2カラムHTML（階層ナビ・active表示・相対リンク）
- ライト/ダークテーマ切り替え
- カテゴリチップ表示とカテゴリ明示指定（`<!-- @category: ... -->`）
- `InputState` の index + 詳細分割
- 関数ページの専用レイアウト化
  - タイトル直下にシグネチャ表示
  - `概要 / 戻り値 / 計算量 / 例外 / 備考 / サンプルコード`
  - 未記載項目は非表示
- 関数ページ用テンプレート追加
  - `docs/reference/source/_templates/function.md`

### 主要ファイル（代表）

- `docs/reference/README.md`
- `docs/reference/source/index.md`
- `docs/reference/source/core/input/*.md`
- `docs/reference/source/core/input/*/*.md`
- `docs/reference/source/adapter/dxlib/*.md`
- `docs/reference/source/adapter/dxlib/*/*.md`
- `docs/reference/site/index.html`
- `docs/reference/site/core/input/**/*.html`
- `docs/reference/site/adapter/dxlib/**/*.html`
- `docs/reference/site/assets/reference.css`
- `tools/generate_reference.py`
- `tools/reference/config.py`
- `tools/reference/renderer.py`
- `tools/reference/sidebar.py`
- `tools/reference/reference.css`
