# adapter::dxlib::DxLibBackend

## 概要

`nx::core::app::IBackend` の DxLib 版です。`launch` に渡すと、DxLib が扱う文字列を UTF-8 にし、DxLib のログファイル (`Log.txt`) を出さないようにします。AI 操作のときは DxLib の窓を隠し、DxLib で画面を保存する撮影の実装を作ります。

## 定義

```cpp
namespace adapter::dxlib {

class DxLibBackend final : public nx::core::app::IBackend {
public:
    void apply_before_init(bool remote_enabled) override;
    auto make_screen_capture() -> std::unique_ptr<nx::core::graphics::IScreenCapture> override;
};

}
```

## 所属レイヤー

Adapter

## 責務

- `DxLib_Init` より前に、DxLib が扱う文字列を UTF-8 にする
- `DxLib_Init` より前に、DxLib が作業フォルダに書くログファイル (`Log.txt`) を止める
- AI 操作のとき、`DxLib_Init` より前に窓を隠し、前面に無くても動くようにする
- DxLib で画面を PNG に保存する撮影の実装を作る

## メンバ関数

| 名前 | 説明 |
|---|---|
| apply_before_init(bool) | 常に `SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8)` と `SetOutApplicationLogValidFlag(FALSE)` を呼ぶ。`true` なら、さらに `SetWindowVisibleFlag(FALSE)` と `SetAlwaysRunFlag(TRUE)` を呼ぶ |
| make_screen_capture() | DxLib での撮影の実装を作る。Release ビルドでは空を返す |

## 備考

- DxLib の既定は Shift_JIS (コードページ 932) です。`DxLibBackend` を使うゲームは、文字列リテラルを UTF-8 でビルドします (MSVC では `/utf-8`)。設定の後に作ったフォントも、追加の指定なしで UTF-8 の文字列を描きます
- 撮影は、`end_frame` を呼んだときの描画先 (`SetDrawScreen` で選んだ画面) を、描画先と同じ大きさの PNG に保存する。PNG はアルファを持たない
- 撮影の実装は `DxLib_Init` より前に作られるが、作るときには DxLib の関数を呼ばない
- 撮影の実装は、Release ビルドの exe には入らない

## サンプルコード

```cpp
#include <DxLib.h>

#include "adapter/dxlib/DxLibBackend.h"
#include "core/app/Launch.h"
#include "core/object/Component.h"

using adapter::dxlib::DxLibBackend;
using nx::core::app::launch;
using nx::core::object::Component;

int main(int argc, char** argv) {
    Component component;
    DxLibBackend backend;
    launch(argc, argv, component, backend);

    ChangeWindowMode(TRUE);
    if (DxLib_Init() == -1) {
        return 1;
    }
    // ゲームの set_input_source とループ

    DxLib_End();
    return 0;
}
```

## 関連項目

- [nx::core::app::IBackend](/D:/work/Project_Core/docs/reference/source/core/app/IBackend.md)
- [nx::core::app::launch](/D:/work/Project_Core/docs/reference/source/core/app/launch.md)
- [nx::core::graphics::IScreenCapture](/D:/work/Project_Core/docs/reference/source/core/graphics/IScreenCapture.md)
