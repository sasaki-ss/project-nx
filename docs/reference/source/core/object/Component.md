# nx::core::object::Component
<!-- @category: class -->

## 概要

シーンやシステム間で共有する基盤コンポーネントです。現在は入力システム (`InputSystem`) へのアクセス窓口を提供します。

## 定義

```cpp
namespace nx::core::object {

class Component final {
public:
    Component() = default;
    ~Component() = default;

    auto input() -> input::InputSystem&;
private:
    input::InputSystem input_system;
};

}
```

## 所属レイヤー

Core

## 責務

- シーンから利用する共通サービスを集約する
- `InputSystem` の所有と参照提供を行う

## メンバ関数

| 名前 | 説明 |
|---|---|
| [Component()](/D:/work/Project_Core/docs/reference/source/core/object/Component/ctor.md) | コンポーネントを構築する |
| [~Component()](/D:/work/Project_Core/docs/reference/source/core/object/Component/dtor.md) | コンポーネントを破棄する |
| [input()](/D:/work/Project_Core/docs/reference/source/core/object/Component/input.md) | 所有する `InputSystem` への参照を返す |

## サンプルコード

```cpp
#include "core/object/Component.h"
#include "core/input/InputState.h"

using nx::core::object::Component;
using nx::core::input::InputState;
using nx::core::input::Key;

int main() {
    Component component;

    component.input().init();
    component.input().update();

    const bool pushed = component.input().get_input(Key::Space, InputState::Pressed);
    (void)pushed;
    return 0;
}
```

## 関連項目

- [nx::core::input::InputSystem](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem.md)
- [nx::core::scene::IScene](/D:/work/Project_Core/docs/reference/source/core/scene/IScene.md)
