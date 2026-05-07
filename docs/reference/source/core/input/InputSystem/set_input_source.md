# nx::core::input::InputSystem::set_input_source

## シグネチャ
```cpp
bool set_input_source(std::unique_ptr<InputBase> input_module);
```

## 概要
入力ソース実装を設定します。

## サンプルコード
```cpp
#include <memory>

#include "core/input/InputSystem.h"
#include "adapter/dxlib/DxLibInput.h"

using nx::core::input::InputSystem;

int main() {
    InputSystem input;
    input.init();

    if (!input.set_input_source(std::make_unique<adapter::dxlib::DxLibInput>())) {
        return 1;
    }

    return 0;
}
```
