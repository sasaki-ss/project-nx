#include "DxLibScreenCapture.h"

#include <DxLib.h>

namespace adapter {
namespace dxlib {

#ifndef NDEBUG

static constexpr int PNG_COMPRESSION_LEVEL = 1;

bool DxLibScreenCapture::save_png(const std::string& path) {
    int width = 0;
    int height = 0;
    if (GetDrawScreenSize(&width, &height) == -1) {
        return false;
    }

    // 描画先のアルファをそのまま保存すると背景が透明な画像になるので、アルファを持たない画像に写してから保存する
    const int image = MakeXRGB8ColorSoftImage(width, height);
    if (image == -1) {
        return false;
    }

    const bool is_saved = GetDrawScreenSoftImage(0, 0, width, height, image) == 0
        && SaveSoftImageToPng(path.c_str(), image, PNG_COMPRESSION_LEVEL) == 0;
    DeleteSoftImage(image);
    return is_saved;
}

#endif

} // namespace dxlib
} // namespace adapter
