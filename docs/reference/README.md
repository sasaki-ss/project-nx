# NX Reference

このディレクトリは Project NX のAPIリファレンスを管理する。

- `source/`: Markdown形式の正本。AI・人間レビュー用。
- `site/`: `source/` から生成したHTML。ローカル閲覧用。

`site/` 配下のHTMLは原則として直接編集しない。  
API仕様を変更する場合は `source/` 配下のMarkdownを更新する。

- 更新履歴: [CHANGELOG.md](/D:/work/Project_Core/docs/reference/CHANGELOG.md)

## サンプルコード運用ルール

- 標準ライブラリ（`std::`）以外の namespace は、原則 `using` 宣言で省略して記述する。
- フル修飾名を使うのは、曖昧さ回避や契約を明示したい場合に限定する。

## カテゴリ判定ルール

- 既定では生成スクリプトが `定義` セクションの記述（`class` / `struct` / `enum class` など）からカテゴリを自動判定する。
- `I` で始まるクラス名は interface 扱いを優先する。
- 明示指定したい場合は、Markdown 冒頭に `<!-- @category: class -->` のようなコメントを追加する。
- 指定可能値: `class`, `struct`, `enum class`, `interface`, `function`, `type`, `category`, `reference`
- 明示指定がある場合は自動判定より優先する。

## 関数ページ運用ルール

- 関数ページは `source` の Markdown 記述に依存してHTML化する。
- `## シグネチャ` は見出しとしては表示せず、タイトル直下にコードブロックとして表示する。
- `## 概要 / 戻り値 / 計算量 / 例外 / 備考 / サンプルコード` は、Markdownに存在する項目のみ表示する（未記載項目は表示しない）。
- 関数ページのベースは [function.md](/D:/work/Project_Core/docs/reference/source/_templates/function.md) を利用する。
