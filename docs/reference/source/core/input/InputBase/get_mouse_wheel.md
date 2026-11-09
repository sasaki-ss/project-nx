# nx::core::input::InputBase::get_mouse_wheel

## シグネチャ
```cpp
int get_mouse_wheel() const;
```

## 概要
前の `update` から回ったホイールの量を、ノッチの数で返します。奥へ回すと正、手前へ回すと負です。

## サンプルコード
```cpp
using nx::core::input::InputBase;

void scroll_list(const InputBase& input, int& scroll_y) {
    // 奥へ回すと一覧の上の方へ戻る
    scroll_y -= input.get_mouse_wheel() * 40;
}
```
