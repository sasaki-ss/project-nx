# nx::core::input::MousePoint

## 概要

マウス座標を表すデータ構造です。

## ヘッダ

```cpp
#include <core/input/InputState.h>
```

## 定義

```cpp
struct MousePoint {
    int x;
    int y;
};
```

## 所属レイヤー

Core

## 責務

- マウス位置を 2 次元座標として保持する
- 座標変換や補正ロジックは担当しない

## メンバ

| 名前 | 型 | 説明 |
|---|---|---|
| x | int | X 座標 |
| y | int | Y 座標 |

## 関連項目

- [nx::core::input::InputBase](/D:/work/Project_Core/docs/reference/source/core/input/InputBase.md)
- [nx::core::input::InputSystem](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem.md)

