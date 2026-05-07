# nx::core::input::InputSystem::get_input(Key, InputState)

## シグネチャ
```cpp
bool get_input(Key key, InputState state);
```

## 概要
キーの入力状態を判定します。

## サンプルコード
```cpp
#include "core/input/InputSystem.h"

using nx::core::input::InputSystem;
using nx::core::input::InputState;
using nx::core::input::Key;

void check_jump(InputSystem& input) {
    if (input.get_input(Key::Space, InputState::Pressed)) {
        // ジャンプ開始処理
    }
}
```
