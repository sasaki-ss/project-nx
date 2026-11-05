# nx::core::graphics::IScreenCapture
<!-- @category: interface -->

## 概要

今の画面を PNG ファイルに保存する口を決めるインターフェースです。実装は、使うライブラリの adapter に置きます。

## 定義

```cpp
namespace nx::core::graphics {

class IScreenCapture {
public:
    virtual ~IScreenCapture() = default;
    virtual bool save_png(const std::string& path) = 0;
};

}
```

## 所属レイヤー

Core

## 責務

- 呼んだ時点の画面の内容を、指定したパスに PNG で保存する口を決める
- 描画ライブラリのことは知らない

## メンバ関数

| 名前 | 説明 |
|---|---|
| save_png(const std::string&) | 今の画面を PNG でパスに保存する。成功時 `true` |

## 備考

- いつ呼ぶかは呼ぶ側が決める。描画を終えた画面を残したいときは、描画の後に呼ぶ
