# nx::core::app::launch
<!-- @category: function -->

## シグネチャ
```cpp
void launch(int argc, char** argv, object::Component& component, IBackend& backend);
```

## 概要
起動時の指定を読み、使うライブラリの初期化前の設定を `backend` にさせます。main の先頭で、`Component` を作った直後に 1 回呼びます。

Debug ビルドで `--nx-remote` があれば AI 操作を有効にします。このとき `component` の入力元を AI が動かす仮想マウスにし、標準入力から命令を受け取り始めます。

## 計算量
起動時の指定の数に比例します。

## 備考
- `Component` を作った直後、ゲームの `set_input_source` より前に呼びます。後に呼んだときの動作は保証しません
- ライブラリの初期化 (`DxLib_Init` など) より前に呼びます。`IBackend::apply_before_init` は初期化前の設定のためです
- 1 回だけ呼びます
- AI 操作が有効なとき、ゲームの `set_input_source` は 2 回目になり、渡した入力元は使われません (`true` が返ります)
- `--nx-` で始まる知らない指定は、警告をログに出して無視します。`--nx-` で始まらない引数は読まず、`argv` から取り除きもしません
- `IBackend::make_screen_capture` が空を返したときは、エラーをログに出し、AI 操作を無効にして普段どおり起動します
- Release ビルドでは、`backend.apply_before_init(false)` だけを呼ぶ inline 関数になります。`--nx-remote` は何もしません

## サンプルコード
```cpp
using nx::core::app::launch;
using nx::core::object::Component;

int main(int argc, char** argv) {
    Component component;
    MyBackend backend; // IBackend を継承した、使うライブラリ用のクラス
    launch(argc, argv, component, backend);

    // ここでライブラリを初期化する (DxLib_Init など)
    // ゲームの set_input_source は launch より後に書く

    return 0;
}
```
