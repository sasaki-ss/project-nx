# nx::core::input::InputState

## 概要

入力の遷移状態を表す列挙型です。

## ヘッダ

```cpp
#include <core/input/InputState.h>
```

## 定義

```cpp
enum class InputState {
    Pressed,
    Down,
    Released
};
```

## 所属レイヤー

Core

## 値

| 値 | 説明 |
|---|---|
| Pressed | このフレームで押された |
| Down | 押下中 |
| Released | このフレームで離された |

## 備考

状態判定ロジックは InputSystem 側に依存します。

## 関連項目

- [nx::core::input::InputSystem](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem.md)
- [nx::core::input::InputState](/D:/work/Project_Core/docs/reference/source/core/input/InputState.md)
