# nx::core::remote::begin_frame
<!-- @category: function -->

## シグネチャ
```cpp
bool begin_frame();
```

## 概要
フレームの頭で、AI から届いている命令を反映します。命令を待たずに戻ります。ゲームのループの条件で、毎フレーム呼びます。

## 戻り値
ループを続けるなら `true` を返します。`quit` が来たとき、または標準入力が終わったときは `false` を返し、その後も `false` を返し続けます。

AI 操作が有効でないときは、常に `true` を返します。

## 計算量
届いている命令の数に比例します。

## 備考
- Release ビルドでは、常に `true` を返す中身の無い inline 関数になります
- 入力の更新 (`InputSystem::update`) より前に呼びます。反映した命令が、そのフレームの入力に入ります

## サンプルコード
```cpp
using nx::core::remote::begin_frame;
using nx::core::remote::end_frame;

while (begin_frame()) {
    update();
    draw();
    end_frame();
    // 画面を切り替える
}
```
