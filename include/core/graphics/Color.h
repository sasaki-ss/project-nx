#ifndef CORE_GRAPHICS_COLOR_H
#define CORE_GRAPHICS_COLOR_H

namespace nx {
namespace core {
namespace graphics {

struct Color {
    int r;
    int g;
    int b;
    int a;

    Color(int r, int g, int b, int a = 255) :
        r(r),
        g(g),
        b(b),
        a(a) {
    }
};

} // namespace graphics
} // namespace core
} // namespace nx

#endif // !CORE_GRAPHICS_COLOR_H
