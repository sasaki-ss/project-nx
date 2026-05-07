# nx::core::input::InputSystem::update

## シグネチャ
```cpp
void update();
```

## 概要
入力状態を更新します。

## サンプルコード
```cpp
#include "core/input/InputSystem.h"

using nx::core::input::InputSystem;

void game_loop(InputSystem& input) {
    while (true) {
        input.update();
        // 入力判定とゲーム更新を行う
        break;
    }
}
```
