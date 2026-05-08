# nx::core::scene::ISceneDirector
<!-- @category: interface -->

## 概要

シーン遷移の操作を抽象化するディレクターインターフェースです。

## 定義

```cpp
namespace nx::core::scene {

enum class SceneChangeMode {
    Pop,
    Push,
    Reset
};

class ISceneDirector {
public:
    typedef std::function<std::unique_ptr<IScene>(object::Component*)> scene_creator_t;

    virtual ~ISceneDirector() = default;
    virtual void open(uint32_t scene_id) = 0;
    virtual void go_to(uint32_t scene_id) = 0;
    virtual void back() = 0;
    virtual void scene_change(uint32_t scene_id, SceneChangeMode mode) = 0;
    virtual void scene_change(SceneChangeMode mode) = 0;
    virtual void set_scene_creator(uint32_t scene_id, scene_creator_t scene_creator) = 0;
};

}
```

## 所属レイヤー

Core

## 責務

- シーンの開始・遷移・復帰操作 API を提供する
- シーン生成関数 (`scene_creator_t`) の登録窓口を提供する

## メンバ関数

| 名前 | 説明 |
|---|---|
| open(uint32_t) | 初回開始向けのシーンオープン |
| go_to(uint32_t) | 現在状態を考慮して指定シーンへ遷移 |
| back() | 1つ前のシーンへ戻る |
| scene_change(uint32_t, SceneChangeMode) | 指定モードでシーン変更 |
| scene_change(SceneChangeMode) | ID 指定なしモード遷移（主に Pop） |
| set_scene_creator(uint32_t, scene_creator_t) | シーンIDと生成関数を紐付ける |

## 関連項目

- [nx::core::scene::IScene](/D:/work/Project_Core/docs/reference/source/core/scene/IScene.md)
- [nx::core::scene::SceneManager](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager.md)
- [nx::core::scene::SceneChangeMode](/D:/work/Project_Core/docs/reference/source/core/scene/SceneChangeMode.md)
