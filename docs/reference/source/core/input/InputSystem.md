# nx::core::input::InputSystem
<!-- @category: class -->

## 概要

Core 側で入力問い合わせを行う集約クラスです。InputBase 実装を差し替えて入力ソースを切り替えます。

## 定義

```cpp
namespace nx::core::input {

class InputSystem final {
public:
    InputSystem();
    ~InputSystem();

    bool init();
    bool set_input_source(std::unique_ptr<InputBase> input_module);
    void update();

    bool get_input(Key key, InputState state);
    bool get_input(Mouse mouse, InputState state);

    std::optional<MousePoint> get_mouse_point();
};

}
```

## 所属レイヤー

Core

## 責務

- アプリケーションからの入力問い合わせ窓口を提供する
- InputBase 実装に依存する箇所を Core 内で閉じ込める
- DxLib など具体ライブラリ API を直接扱わない

## コンストラクタ

| 名前 | 説明 |
|---|---|
| InputSystem() | 入力システムを構築する |
| ~InputSystem() | 入力システムを破棄する |

## メンバ関数

| 名前 | 説明 |
|---|---|
| [init](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem/init.md) | 入力システム初期化 |
| [set_input_source](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem/set_input_source.md) | 入力ソース実装を設定 |
| [update](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem/update.md) | 入力状態更新 |
| [get_input(Key, InputState)](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem/get_input_key.md) | キー入力状態問い合わせ |
| [get_input(Mouse, InputState)](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem/get_input_mouse.md) | マウス入力状態問い合わせ |
| [get_mouse_point](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem/get_mouse_point.md) | マウス座標問い合わせ |

## サンプルコード

```cpp
#include <memory>

#include "core/input/InputSystem.h"
#include "adapter/dxlib/DxLibInput.h"

using nx::core::input::InputSystem;
using nx::core::input::InputState;
using nx::core::input::Key;

int main() {
    InputSystem input;

    if (!input.init()) {
        return 1;
    }

    if (!input.set_input_source(std::make_unique<adapter::dxlib::DxLibInput>())) {
        return 1;
    }

    while (true) {
        input.update();

        if (input.get_input(Key::Esc, InputState::Pressed)) {
            break;
        }

        // Scene更新・描画などを行う
    }

    return 0;
}
```

## 関連項目

- [nx::core::input::InputBase](/D:/work/Project_Core/docs/reference/source/core/input/InputBase.md)
- [nx::core::input::InputState::InputState](/D:/work/Project_Core/docs/reference/source/core/input/InputState/InputState.md)
- [adapter::dxlib::DxLibInput](/D:/work/Project_Core/docs/reference/source/adapter/dxlib/DxLibInput.md)




