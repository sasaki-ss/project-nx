# nx::core::input::InputSystem::set_input_source

## シグネチャ
```cpp
bool set_input_source(std::unique_ptr<InputBase> input_module);
```

## 概要
入力ソース実装を設定します。設定できるのは 1 回だけです。
すでに設定されているときは、渡された入力ソースを使わずに警告をログに出します。
AI 操作 (`--nx-remote`) では nx がゲームより先に仮想マウスを設定するので、ゲームの設定は使われません。

## 戻り値
設定できた場合と、すでに設定されていて渡された入力ソースを使わなかった場合は `true`。
`input_module` が空の場合と、入力ソースの `init` が `false` を返した場合は `false`。このときは設定されないので、もう一度呼べます。

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
