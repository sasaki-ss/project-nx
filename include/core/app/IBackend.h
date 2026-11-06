#ifndef CORE_APP_INTERFACE_BACKEND_H
#define CORE_APP_INTERFACE_BACKEND_H

#include <memory>

#include "core/graphics/IScreenCapture.h"

namespace nx {
namespace core {
namespace app {

class IBackend {
public:
    virtual ~IBackend() = default;
    virtual void apply_before_init(bool remote_enabled) = 0;
    virtual auto make_screen_capture() -> std::unique_ptr<graphics::IScreenCapture> = 0;
};

} // namespace app
} // namespace core
} // namespace nx

#endif // !CORE_APP_INTERFACE_BACKEND_H
