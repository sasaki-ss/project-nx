# adapter::dxlib::DxLibInput::DxLibInput

## シグネチャ
```cpp
DxLibInput() = default;
```

## 概要
DxLib 入力アダプタを構築します。

## サンプルコード
```cpp
#include <memory>

#include "adapter/dxlib/DxLibInput.h"

int main() {
    auto input = std::make_unique<adapter::dxlib::DxLibInput>();
    // この後 InputSystem へ設定する
    return 0;
}
```
