# nx::core::app::IBackend
<!-- @category: interface -->

## 概要

使うライブラリ (DxLib など) ごとの、起動時の準備を決めるインターフェースです。`launch` が呼びます。実装は、使うライブラリの adapter に置きます。

## 定義

```cpp
namespace nx::core::app {

class IBackend {
public:
    virtual ~IBackend() = default;
    virtual void apply_before_init(bool remote_enabled) = 0;
    virtual auto make_screen_capture() -> std::unique_ptr<graphics::IScreenCapture> = 0;
};

}
```

## 所属レイヤー

Core

## 責務

- ライブラリの初期化より前に要る設定をする口を決める
- AI 操作の `shot` で使う、撮影の実装を作る口を決める
- ライブラリのことは知らない

## メンバ関数

| 名前 | 説明 |
|---|---|
| apply_before_init(bool) | ライブラリの初期化前の設定をする。AI 操作が有効なら `true` が渡る。そのときは窓を隠し、前面に無くても動くようにする |
| make_screen_capture() | 撮影の実装を作る。作れなければ空を返す |

## 備考

- `apply_before_init` は、普段の起動でも Release ビルドでも、`launch` から必ず 1 回呼ばれる
- `make_screen_capture` は、Debug ビルドで `--nx-remote` があるときだけ、`apply_before_init` より先に呼ばれる
- `make_screen_capture` が空を返すと、`launch` は AI 操作を無効にし、`apply_before_init` に `false` を渡す
- `make_screen_capture` はライブラリの初期化前に呼ばれるので、撮影の実装は作るときにライブラリの関数を呼ばない

## 関連項目

- [adapter::dxlib::DxLibBackend](/D:/work/Project_Core/docs/reference/source/adapter/dxlib/DxLibBackend.md)
- [nx::core::app::launch](/D:/work/Project_Core/docs/reference/source/core/app/launch.md)
