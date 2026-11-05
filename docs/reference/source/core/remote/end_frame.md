# nx::core::remote::end_frame
<!-- @category: function -->

## シグネチャ
```cpp
void end_frame();
```

## 概要
描き終えて画面を切り替える前に呼びます。`shot` の命令が来ていれば、このときの画面を保存して返事を書きます。

## 計算量
`shot` が来ていないフレームは O(1) です。撮影するフレームは、画面を PNG に保存する時間がかかります。

## 備考
- AI 操作が有効でないときは、何もしません
- Release ビルドでは、中身の無い inline 関数になります

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
