# nx::core::input::InputSystem::get_mouse_point

## シグネチャ
```cpp
std::optional<MousePoint> get_mouse_point();
```

## 概要
取得可能な場合にマウス座標を返します。

## サンプルコード
```cpp
#include "core/input/InputSystem.h"

using nx::core::input::InputSystem;

void draw_cursor_info(InputSystem& input) {
    auto p = input.get_mouse_point();
    if (!p) return;
    // p->x, p->y を描画に利用する
}
```
