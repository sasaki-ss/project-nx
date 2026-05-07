# nx::core::input::InputSystem::get_input(Mouse, InputState)

## シグネチャ
```cpp
bool get_input(Mouse mouse, InputState state);
```

## 概要
マウスボタンの入力状態を判定します。

## サンプルコード
```cpp
#include "core/input/InputSystem.h"

using nx::core::input::InputSystem;
using nx::core::input::InputState;
using nx::core::input::Mouse;

void check_click(InputSystem& input) {
    if (input.get_input(Mouse::Left, InputState::Pressed)) {
        // クリック時の処理
    }
}
```
