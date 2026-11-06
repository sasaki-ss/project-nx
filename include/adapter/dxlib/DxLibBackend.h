#ifndef ADAPTER_DXLIB_DXLIBBACKEND_H
#define ADAPTER_DXLIB_DXLIBBACKEND_H

#include <memory>

#include "core/app/IBackend.h"

namespace adapter {
namespace dxlib {

class DxLibBackend final : public nx::core::app::IBackend {
public:
    void apply_before_init(bool remote_enabled) override;
    auto make_screen_capture() -> std::unique_ptr<nx::core::graphics::IScreenCapture> override;
};

} // namespace dxlib
} // namespace adapter

#endif // !ADAPTER_DXLIB_DXLIBBACKEND_H
