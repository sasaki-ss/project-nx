# nx::core::scene

## 概要

Project NX のシーン遷移・シーン実行に関する Core レイヤーの API 群です。

## インターフェース

| 名前 | 説明 |
|---|---|
| [IScene](/D:/work/Project_Core/docs/reference/source/core/scene/IScene.md) | 各シーン実装が満たす実行契約 |
| [ISceneDirector](/D:/work/Project_Core/docs/reference/source/core/scene/ISceneDirector.md) | シーン遷移操作を提供する契約 |

## クラス

| 名前 | 説明 |
|---|---|
| [SceneManager](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager.md) | `ISceneDirector` 実装。シーンスタック管理と遷移確定を担う |

## 列挙型

| 名前 | 説明 |
|---|---|
| [SceneChangeMode](/D:/work/Project_Core/docs/reference/source/core/scene/SceneChangeMode.md) | シーン切り替え方式（Pop/Push/Reset） |

## 関連

- [nx::core::object](/D:/work/Project_Core/docs/reference/source/core/object/index.md)
