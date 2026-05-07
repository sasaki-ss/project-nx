# nx::core::input::InputSystem::~InputSystem

## シグネチャ
```cpp
~InputSystem();
```

## 概要
入力システムを破棄します。

## サンプルコード
```cpp
#include "core/input/InputSystem.h"

using nx::core::input::InputSystem;

void scope_end() {
    InputSystem input;
    // スコープを抜けると破棄される
}
```
