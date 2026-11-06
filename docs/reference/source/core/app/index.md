# nx::core::app

## 概要

ゲームの起動に関する Core レイヤーの API 群です。main の先頭で `launch` を呼び、起動時の指定を nx に読ませます。

## インターフェース

| 名前 | 説明 |
|---|---|
| [IBackend](/D:/work/Project_Core/docs/reference/source/core/app/IBackend.md) | 使うライブラリの、初期化前の設定と撮影の実装を作る口 |

## 関数

| 名前 | 説明 |
|---|---|
| [launch](/D:/work/Project_Core/docs/reference/source/core/app/launch.md) | 起動時の指定を読み、ライブラリの初期化前の設定をさせる。`--nx-remote` なら AI 操作を有効にする |

## 起動時の指定

nx の指定はすべて `--nx-` で始まります。`--nx-` で始まらない引数はゲーム自身のものとして、読まずにそのまま残します。

| 指定 | すること |
|---|---|
| `--nx-remote` | AI 操作を有効にする (Debug ビルドだけ)。命令と返事は [nx::core::remote](/D:/work/Project_Core/docs/reference/source/core/remote/index.md) を参照 |

- 知らない `--nx-` の指定は、警告をログに出して無視する

## 関連

- [nx::core::remote](/D:/work/Project_Core/docs/reference/source/core/remote/index.md)
- [nx::core::object::Component](/D:/work/Project_Core/docs/reference/source/core/object/Component.md)
- [nx::core::graphics::IScreenCapture](/D:/work/Project_Core/docs/reference/source/core/graphics/IScreenCapture.md)
