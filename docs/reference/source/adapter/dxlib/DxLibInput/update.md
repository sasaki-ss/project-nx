# adapter::dxlib::DxLibInput::update

## シグネチャ
```cpp
void update() override;
```

## 概要
DxLib の入力値を取得し、`InputBase` の保持状態を更新します。

## サンプルコード
```cpp
#include "adapter/dxlib/DxLibInput.h"

void poll_once(adapter::dxlib::DxLibInput& input) {
    input.update();
    // 更新後の状態を InputSystem 側が参照する
}
```
