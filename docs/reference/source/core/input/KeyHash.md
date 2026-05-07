# nx::core::input::KeyHash

## 概要

`Key` を `std::unordered_map` のキーとして利用するためのハッシュ関数オブジェクトです。

## ヘッダ

```cpp
#include <core/input/InputState.h>
```

## 定義

```cpp
struct KeyHash {
    std::size_t operator()(Key key) const noexcept;
};
```

## 所属レイヤー

Core

## メンバ関数

| 名前 | 説明 |
|---|---|
| operator() | Key を整数値に変換してハッシュ値を返す |

## 関連項目

- [nx::core::input::Key](/D:/work/Project_Core/docs/reference/source/core/input/Key.md)

