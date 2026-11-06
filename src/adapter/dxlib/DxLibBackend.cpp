#include "adapter/dxlib/DxLibBackend.h"

#include <DxLib.h>

#include "DxLibScreenCapture.h"

namespace adapter {
namespace dxlib {

void DxLibBackend::apply_before_init(bool remote_enabled) {
    if (!remote_enabled) {
        return;
    }

    SetWindowVisibleFlag(FALSE);
    SetAlwaysRunFlag(TRUE);
}

auto DxLibBackend::make_screen_capture() -> std::unique_ptr<nx::core::graphics::IScreenCapture> {
#ifndef NDEBUG
    return std::make_unique<DxLibScreenCapture>();
#else
    return nullptr;
#endif
}

} // namespace dxlib
} // namespace adapter
