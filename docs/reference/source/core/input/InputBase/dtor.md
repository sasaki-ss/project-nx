# nx::core::input::InputBase::~InputBase

## シグネチャ
```cpp
virtual ~InputBase() = default;
```

## 概要
仮想デストラクタです。

## サンプルコード
```cpp
using nx::core::input::InputBase;

class DummyInput final : public InputBase {
public:
    ~DummyInput() override = default;
    bool init() override { return true; }
    void update() override {}
};
```
