# nx::core::input::Mouse

## 概要

マウスボタン識別子を表す列挙型です。

## ヘッダ

```cpp
#include <core/input/InputState.h>
```

## 定義

```cpp
enum class Mouse {
    Left,
    Right,
    Middle,
    Extra1,
    Extra2,
    Count
};
```

## 所属レイヤー

Core

## 値

| 値 | 説明 |
|---|---|
| Left | 左ボタン |
| Right | 右ボタン |
| Middle | 中央ボタン |
| Extra1 | 拡張ボタン1 |
| Extra2 | 拡張ボタン2 |
| Count | 要素数管理用 |

## 備考

具体的なボタン番号は Adapter 側でマッピングします。

## 関連項目

- [nx::core::input::MouseHash](/D:/work/Project_Core/docs/reference/source/core/input/MouseHash.md)
- [nx::core::input::MousePoint](/D:/work/Project_Core/docs/reference/source/core/input/MousePoint.md)

