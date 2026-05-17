#include "adapter/dxlib/DxLibDrawHelper.h"

#include <DxLib.h>

using nx::core::graphics::Color;

static constexpr int ALPHA_MAX = 255;

namespace adapter {
namespace dxlib {

void DxLibDrawHelper::draw_box(float x, float y, float x2, float y2, Color color) {
    if (color.a < ALPHA_MAX) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);
        DrawBoxAA(x, y, x2, y2, GetColor(color.r, color.g, color.b), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    } else {
        DrawBoxAA(x, y, x2, y2, GetColor(color.r, color.g, color.b), TRUE);
    }
}

void DxLibDrawHelper::draw_string(float x, float y, std::string str, Color color) {
    if (color.a < ALPHA_MAX) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.a);
        DrawStringF(x, y, str.c_str(), GetColor(color.r, color.g, color.b));
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    } else {
        DrawStringF(x, y, str.c_str(), GetColor(color.r, color.g, color.b));
    }
}

int DxLibDrawHelper::get_draw_string_width(std::string str, int len) {
    return GetDrawStringWidth(str.c_str(), len);
}

int DxLibDrawHelper::get_font_size() {
    return GetFontSize();
}

} // namespace dxlib
} // namespace adapter