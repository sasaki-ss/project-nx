# NX Reference Changelog

## 2026-11-06 (DxLibBackend)

- `adapter::dxlib::DxLibBackend` のページを追加し、adapter/dxlib の一覧に追加。一覧の概要を、入力だけの説明から広げた
- `launch` のサンプルコードを `DxLibBackend` を使う形にし、`IBackend` のページに関連項目を追加
- `site/` を再生成した

## 2026-11-06 (launch の Release)

- `launch` の備考で、Release ビルドの動きを「inline 関数になる」から「`--nx-remote` は何もせず、`apply_before_init` に `false` を渡す」に直した
- `site/` を再生成した

## 2026-11-06 (launch)

- `nx::core::app` のページを追加し、`IBackend` と `launch` のページと、起動時の指定の一覧を追加
- `nx::core::remote` の概要に、AI 操作が有効になる条件 (`--nx-remote` と `launch`) を追記
- レイヤー別インデックスに Core App を追加
- `site/` を再生成した

## 2026-11-06 (remote)

- `nx::core::remote` のページを追加し、`begin_frame` / `end_frame` のページと、AI 操作の命令と返事の一覧を追加
- レイヤー別インデックスに Core Remote を追加
- `site/` を再生成した

## 2026-11-06 (IScreenCapture)

- `nx::core::graphics` のページを追加し、`IScreenCapture` のページを追加
- レイヤー別インデックスに Core Graphics を追加
- `site/` を再生成した

## 2026-11-05 (InputSystem 入力ソースは 1 回だけ)

- `InputSystem::set_input_source` に、設定できるのは 1 回だけであることと、戻り値の条件を追記
- `InputSystem` のメンバ関数一覧の説明を更新
- `site/` を再生成した

## 2026-11-05 (site 再生成)

- `source/` に合わせて `site/` を再生成した。Logger・`SceneManager::set_initial_scene`・動作環境 (C++20) が `site/` にも反映された

## 2026-11-05 (C++20)

- 推奨する C++ のバージョンを C++20 以上にし、トップページに「動作環境」を追加
- `site/` は再生成していない

## 2026-11-05 (Logger)

- `nx::core::util` を追加し、`Logger` / `LogLevel` / `LogMessage` と `Logger` の各関数のページを追加
- レイヤー別インデックスに Core Util を追加
- `site/` は再生成していない

## 2026-11-05 (SceneManager Lifecycle)

- `SceneManager::set_initial_scene` のページを追加し、定義とメンバ関数一覧に追記
- `SceneManager::init` に、初期シーンの生成と戻り値の条件を追記
- `SceneManager::~SceneManager` が `end` を呼ぶことを追記
- `SceneManager::update` / `draw` の、シーンが積まれていないときの動作を追記
- `site/` は再生成していない

## 2026-05-12 (Scene Reference Sync)

- `develop` のシーン API に合わせて `IScene::update(ISceneDirector&)` の記述へ更新
- `SceneManager::update()` が自身を `ISceneDirector&` として現在シーンへ渡す説明を追加
- SceneManager 設計メモの更新サンプルとライフサイクル表を現行 API に同期

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
