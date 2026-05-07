# nx::core::input::InputBase::update

## シグネチャ
```cpp
virtual void update() = 0;
```

## 概要
現在フレームの入力状態に更新します。

## サンプルコード
```cpp
using nx::core::input::InputBase;
using nx::core::input::Key;
using nx::core::input::Mouse;

class DummyInput final : public InputBase {
public:
    bool init() override { return true; }
    void update() override {
        // 外部入力APIから値を読み取り、内部状態を更新する
        key_state[Key::Space] = true;
        mouse_state[Mouse::Left] = false;
    }
};
```
