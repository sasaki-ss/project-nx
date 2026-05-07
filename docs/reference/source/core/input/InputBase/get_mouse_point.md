# nx::core::input::InputBase::get_mouse_point

## シグネチャ
```cpp
const MousePoint& get_mouse_point() const;
```

## 概要
マウスカーソル座標を参照します。

## サンプルコード
```cpp
using nx::core::input::InputBase;

void draw_cursor(const InputBase& input) {
    const auto& p = input.get_mouse_point();
    // p.x, p.y を使ってUI上にカーソル情報を出す
    (void)p;
}
```
