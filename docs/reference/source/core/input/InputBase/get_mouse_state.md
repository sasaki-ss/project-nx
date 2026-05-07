# nx::core::input::InputBase::get_mouse_state

## シグネチャ
```cpp
const std::unordered_map<Mouse, bool, MouseHash>& get_mouse_state() const;
```

## 概要
マウスボタン状態マップを参照します。

## サンプルコード
```cpp
using nx::core::input::InputBase;
using nx::core::input::Mouse;

void dump_left(const InputBase& input) {
    const auto& buttons = input.get_mouse_state();
    auto it = buttons.find(Mouse::Left);
    // 見つかったら押下状態を参照する
    (void)it;
}
```
