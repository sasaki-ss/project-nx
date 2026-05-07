# nx::core::input::InputBase::InputBase

## シグネチャ
```cpp
InputBase() = default;
```

## 概要
デフォルトコンストラクタです。

## サンプルコード
```cpp
using nx::core::input::InputBase;

class DummyInput final : public InputBase {
public:
    DummyInput() = default;
    bool init() override { return true; }
    void update() override {}
};
```
