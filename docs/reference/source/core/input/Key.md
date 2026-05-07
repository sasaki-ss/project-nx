# nx::core::input::Key

## 概要

キーボード入力の識別子を表す列挙型です。

## ヘッダ

```cpp
#include <core/input/InputState.h>
```

## 定義

```cpp
enum class Key {
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Space, Enter, Esc,
    ArrowUp, ArrowDown, ArrowLeft, ArrowRight,
    LShift, RShift, LCtrl, RCtrl,
    Count
};
```

## 所属レイヤー

Core

## 値

| 値 | 説明 |
|---|---|
| A..Z | 英字キー |
| Space | スペースキー |
| Enter | Enter キー |
| Esc | Esc キー |
| ArrowUp/Down/Left/Right | 矢印キー |
| LShift/RShift | Shift キー |
| LCtrl/RCtrl | Ctrl キー |
| Count | 要素数管理用 |

## 備考

具体ライブラリのキーコードは Adapter 側で吸収します。

## 関連項目

- [nx::core::input::KeyHash](/D:/work/Project_Core/docs/reference/source/core/input/KeyHash.md)
- [adapter::dxlib::DxLibInput](/D:/work/Project_Core/docs/reference/source/adapter/dxlib/DxLibInput.md)

