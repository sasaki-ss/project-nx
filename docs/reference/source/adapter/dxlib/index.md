# adapter::dxlib

## 概要

DxLib を使った Adapter レイヤーの API 群です。入力の取得と、起動時の準備 (AI 操作の窓と撮影) を受け持ちます。

## クラス

| 名前 | 説明 |
|---|---|
| [DxLibBackend](/D:/work/Project_Core/docs/reference/source/adapter/dxlib/DxLibBackend.md) | `launch` に渡す、DxLib 用の起動時の準備。AI 操作のときに窓を隠し、撮影の実装を作る |
| [DxLibInput](/D:/work/Project_Core/docs/reference/source/adapter/dxlib/DxLibInput.md) | DxLib の入力を Core 入力契約へ変換するアダプタ |

## 関連

- [nx::core::app](/D:/work/Project_Core/docs/reference/source/core/app/index.md)
- [nx::core::input](/D:/work/Project_Core/docs/reference/source/core/input/index.md)
