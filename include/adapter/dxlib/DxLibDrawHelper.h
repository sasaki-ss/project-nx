#ifndef ADAPTER_DXLIB_DXLIBDRAWHELPER_H
#define ADAPTER_DXLIB_DXLIBDRAWHELPER_H

#include "core/graphics/Color.h"
#include <string>

namespace adapter {
namespace dxlib {

class DxLibDrawHelper final {
public:
    DxLibDrawHelper() = default;
    ~DxLibDrawHelper() = default;
    void draw_box(float x, float y, float x2, float y2, nx::core::graphics::Color color, bool is_fill = true) const;
    void draw_string(float x, float y, const std::string& str, nx::core::graphics::Color color) const;
    int get_draw_string_width(const std::string& str, int len) const;
    int get_font_size() const;
};

} // namespace dxlib
} // namespace adapter

#endif // !ADAPTER_DXLIB_DXLIBDRAWHELPER_H
