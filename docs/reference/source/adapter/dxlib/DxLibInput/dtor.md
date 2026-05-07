# adapter::dxlib::DxLibInput::~DxLibInput

## シグネチャ
```cpp
~DxLibInput() override = default;
```

## 概要
DxLib 入力アダプタを破棄します。

## サンプルコード
```cpp
#include "adapter/dxlib/DxLibInput.h"

void release_adapter() {
    adapter::dxlib::DxLibInput input;
    // スコープ終了時に破棄される
}
```
