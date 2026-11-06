#ifndef ADAPTER_DXLIB_DXLIBSCREENCAPTURE_H
#define ADAPTER_DXLIB_DXLIBSCREENCAPTURE_H

#include <string>

#include "core/graphics/IScreenCapture.h"

namespace adapter {
namespace dxlib {

class DxLibScreenCapture final : public nx::core::graphics::IScreenCapture {
public:
    bool save_png(const std::string& path) override;
};

} // namespace dxlib
} // namespace adapter

#endif // !ADAPTER_DXLIB_DXLIBSCREENCAPTURE_H
