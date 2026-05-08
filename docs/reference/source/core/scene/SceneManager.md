# nx::core::scene::SceneManager
<!-- @category: class -->

## 概要

`ISceneDirector` を実装し、シーンスタック管理と遷移確定処理を担当するクラスです。

## 定義

```cpp
namespace nx::core::scene {

class SceneManager final : public ISceneDirector {
public:
    SceneManager(object::Component* component);
    ~SceneManager();
    bool init();
    void end();
    void update();
    void draw();

    void open(uint32_t scene_id) override;
    void go_to(uint32_t scene_id) override;
    void back() override;
    void scene_change(uint32_t scene_id, SceneChangeMode mode) override;
    void scene_change(SceneChangeMode mode) override;
    void set_scene_creator(uint32_t scene_id, scene_creator_t scene_creator) override;
};

}
```

## 所属レイヤー

Core

## 責務

- シーンスタックのライフサイクル管理
- 遷移要求の保留とコミット処理
- シーンIDに紐づく生成関数からのシーン生成

## メンバ関数

| 名前 | 説明 |
|---|---|
| [SceneManager(Component*)](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/ctor.md) | 共有コンポーネント参照でシーン管理を構築する |
| [~SceneManager()](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/dtor.md) | シーン管理を破棄する |
| [init()](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/init.md) | 初期シーン開始準備 |
| [end()](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/end.md) | 保持中シーンの終了処理 |
| [update()](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/update.md) | シーン更新と遷移コミット |
| [draw()](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/draw.md) | 現在シーンの描画 |
| [open(uint32_t)](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/open.md) | 指定IDのシーンを開く |
| [go_to(uint32_t)](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/go_to.md) | 指定IDのシーンへ遷移 |
| [back()](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/back.md) | 1つ前のシーンへ戻る |
| [scene_change(uint32_t, SceneChangeMode)](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/scene_change_with_id.md) | モード指定でシーン遷移 |
| [scene_change(SceneChangeMode)](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/scene_change.md) | モードのみ指定の遷移 |
| [set_scene_creator(uint32_t, scene_creator_t)](/D:/work/Project_Core/docs/reference/source/core/scene/SceneManager/set_scene_creator.md) | シーン生成関数を登録 |

## 関連項目

- [nx::core::scene::ISceneDirector](/D:/work/Project_Core/docs/reference/source/core/scene/ISceneDirector.md)
- [nx::core::scene::IScene](/D:/work/Project_Core/docs/reference/source/core/scene/IScene.md)
- [nx::core::object::Component](/D:/work/Project_Core/docs/reference/source/core/object/Component.md)
