# nx::core::input::InputBase::init

## シグネチャ
```cpp
virtual bool init() = 0;
```

## 概要
入力ソースの初期化を行います。

## サンプルコード
```cpp
using nx::core::input::InputBase;
using nx::core::input::Key;

class DummyInput final : public InputBase {
public:
    bool init() override {
        key_state[Key::Space] = false;
        return true;
    }
    void update() override {}
};
```
