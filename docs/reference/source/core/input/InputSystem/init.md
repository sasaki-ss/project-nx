# nx::core::input::InputSystem::init

## シグネチャ
```cpp
bool init();
```

## 概要
入力システムを初期化します。

## サンプルコード
```cpp
#include "core/input/InputSystem.h"

using nx::core::input::InputSystem;

int main() {
    InputSystem input;

    if (!input.init()) {
        return 1;
    }

    // input.set_input_source(...) を行う
    // メインループで input.update() を行う
    // 入力判定とアプリケーション処理を行う

    return 0;
}
```
