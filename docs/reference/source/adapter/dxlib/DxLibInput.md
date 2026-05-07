# adapter::dxlib::DxLibInput

## 概要

DxLib から入力状態を取得し、Core の `InputBase` 契約に合わせて提供する Adapter 実装です。

## 定義

```cpp
namespace adapter::dxlib {

class DxLibInput final : public nx::core::input::InputBase {
public:
    DxLibInput() = default;
    ~DxLibInput() override = default;

    bool init() override;
    void update() override;
};

}
```

## 所属レイヤー

Adapter

## 責務

- DxLib の入力 API と Core 入力 API の差分を吸収する
- Core が具体ライブラリに依存しない構成を維持する
- アプリケーションロジックは担当しない

## コンストラクタ

| 名前 | 説明 |
|---|---|
| DxLibInput() | DxLib 入力アダプタを構築する |
| ~DxLibInput() | DxLib 入力アダプタを破棄する |

## メンバ関数

| 名前 | 説明 |
|---|---|
| [init](/D:/work/Project_Core/docs/reference/source/adapter/dxlib/DxLibInput/init.md) | DxLib 側の入力利用準備 |
| [update](/D:/work/Project_Core/docs/reference/source/adapter/dxlib/DxLibInput/update.md) | DxLib から現在入力状態を取り込み |

## サンプルコード

```cpp
using nx::core::input::InputBase;

int main() {
    auto module = std::make_unique<adapter::dxlib::DxLibInput>();
    InputBase* input = module.get();
    input->init();
    input->update();
    return 0;
}
```

## 関連項目

- [nx::core::input::InputBase](/D:/work/Project_Core/docs/reference/source/core/input/InputBase.md)
- [nx::core::input::InputSystem](/D:/work/Project_Core/docs/reference/source/core/input/InputSystem.md)
