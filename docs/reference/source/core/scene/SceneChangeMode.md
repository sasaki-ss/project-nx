# nx::core::scene::SceneChangeMode
<!-- @category: enum class -->

## 概要

シーン切り替え時のスタック操作モードを表す列挙型です。

## 定義

```cpp
namespace nx::core::scene {

enum class SceneChangeMode {
    Pop,
    Push,
    Reset
};

}
```

## 列挙子

| 名前 | 説明 |
|---|---|
| Pop | 現在シーンを終了して 1 つ前へ戻る |
| Push | 現在シーンを保持したまま新しいシーンを積む |
| Reset | 現在までのシーンを破棄して指定シーンへ切り替える |

## 関連項目

- [nx::core::scene::ISceneDirector](/D:/work/Project_Core/docs/reference/source/core/scene/ISceneDirector.md)
- [nx::core::scene::SceneManager](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager.md)
