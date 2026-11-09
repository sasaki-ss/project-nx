# nx::core::input::InputSystem::get_mouse_wheel

## シグネチャ
```cpp
std::optional<int> get_mouse_wheel();
```

## 概要
前の `update` から回ったホイールの量を、ノッチの数で返します。奥へ回すと正、手前へ回すと負です。入力ソースが設定されていないときは空を返します。

## 備考
- AI 操作 (`--nx-remote`) では、`wheel` 命令で回した量を返します

## サンプルコード
```cpp
#include "core/input/InputSystem.h"

using nx::core::input::InputSystem;

void scroll_list(InputSystem& input, int& scroll_y) {
    auto wheel = input.get_mouse_wheel();
    if (!wheel) return;
    scroll_y -= *wheel * 40;
}
```
