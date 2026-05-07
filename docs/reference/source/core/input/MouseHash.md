# nx::core::input::MouseHash

## 概要

`Mouse` を `std::unordered_map` のキーとして利用するためのハッシュ関数オブジェクトです。

## ヘッダ

```cpp
#include <core/input/InputState.h>
```

## 定義

```cpp
struct MouseHash {
    std::size_t operator()(Mouse mouse) const noexcept;
};
```

## 所属レイヤー

Core

## メンバ関数

| 名前 | 説明 |
|---|---|
| operator() | Mouse を整数値に変換してハッシュ値を返す |

## 関連項目

- [nx::core::input::Mouse](/D:/work/Project_Core/docs/reference/source/core/input/Mouse.md)

