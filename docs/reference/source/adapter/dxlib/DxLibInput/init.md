# adapter::dxlib::DxLibInput::init

## シグネチャ
```cpp
bool init() override;
```

## 概要
DxLib の入力利用前提を満たす初期化を行います。

## サンプルコード
```cpp
#include "adapter/dxlib/DxLibInput.h"

int main() {
    adapter::dxlib::DxLibInput input;

    if (!input.init()) {
        return 1;
    }

    // InputSystem に組み込む
    return 0;
}
```
