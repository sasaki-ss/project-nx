#ifndef CORE_GRAPHICS_INTERFACE_SCREEN_CAPTURE_H
#define CORE_GRAPHICS_INTERFACE_SCREEN_CAPTURE_H

#include <string>

namespace nx {
namespace core {
namespace graphics {

class IScreenCapture {
public:
    virtual ~IScreenCapture() = default;
    virtual bool save_png(const std::string& path) = 0;
};

} // namespace graphics
} // namespace core
} // namespace nx

#endif // !CORE_GRAPHICS_INTERFACE_SCREEN_CAPTURE_H
