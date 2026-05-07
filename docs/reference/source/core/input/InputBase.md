# nx::core::input::InputBase
<!-- @category: class -->

## 概要

入力取得の抽象基底クラスです。Core 側はこの契約を通して入力状態を参照します。

## 定義

```cpp
namespace nx::core::input {

class InputBase {
public:
    InputBase() = default;
    virtual ~InputBase() = default;

    virtual bool init() = 0;
    virtual void update() = 0;

    const std::unordered_map<Key, bool, KeyHash>& get_key_state() const;
    const std::unordered_map<Mouse, bool, MouseHash>& get_mouse_state() const;
    const MousePoint& get_mouse_point() const;
};

}
```

## 所属レイヤー

Core

## 責務

- 入力ソースが満たすべき最小契約を定義する
- キー・マウス状態の参照口を提供する
- 実際の入力ライブラリ呼び出しは担当しない

## コンストラクタ

| 名前 | 説明 |
|---|---|
| InputBase() | デフォルト構築する |
| ~InputBase() | 仮想デストラクタ |

## メンバ関数

| 名前 | 説明 |
|---|---|
| [init](/D:/work/Project_Core/docs/reference/source/core/input/InputBase/init.md) | 入力モジュール初期化 |
| [update](/D:/work/Project_Core/docs/reference/source/core/input/InputBase/update.md) | フレームごとの入力更新 |
| [get_key_state](/D:/work/Project_Core/docs/reference/source/core/input/InputBase/get_key_state.md) | キー押下状態マップ取得 |
| [get_mouse_state](/D:/work/Project_Core/docs/reference/source/core/input/InputBase/get_mouse_state.md) | マウス押下状態マップ取得 |
| [get_mouse_point](/D:/work/Project_Core/docs/reference/source/core/input/InputBase/get_mouse_point.md) | マウス座標取得 |

## サンプルコード

```cpp
using nx::core::input::InputBase;

class DummyInput final : public InputBase {
public:
    bool init() override { return true; }
    void update() override {
        // key_state / mouse_state / mouse_point を更新する
    }
};
```

## 関連項目

- [nx::core::input::InputSystem](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem.md)
- [adapter::dxlib::DxLibInput](/D:/work/Project_Core/docs/reference/source/adapter/dxlib/DxLibInput.md)



