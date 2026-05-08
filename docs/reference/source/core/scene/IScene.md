# nx::core::scene::IScene
<!-- @category: interface -->

## 概要

アプリケーション内の各シーン実装が従う基底インターフェースです。

## 定義

```cpp
namespace nx::core::scene {

class IScene {
protected:
    object::Component* comp;
public:
    IScene(object::Component* comp);
    virtual ~IScene() = default;

    virtual bool init() = 0;
    virtual void end() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};

}
```

## 所属レイヤー

Core

## 責務

- シーンライフサイクル（`init` / `end`）を統一する
- フレーム更新（`update` / `draw`）契約を提供する

## メンバ関数

| 名前 | 説明 |
|---|---|
| IScene(Component*) | 共有コンポーネントを受け取ってシーンを構築する |
| init() | シーン初期化。成功時 `true` |
| end() | シーン終了処理 |
| update() | シーン更新 |
| draw() | シーン描画 |

## 関連項目

- [nx::core::object::Component](/D:/work/Project_Core/docs/reference/source/core/object/Component.md)
- [nx::core::scene::ISceneDirector](/D:/work/Project_Core/docs/reference/source/core/scene/ISceneDirector.md)
