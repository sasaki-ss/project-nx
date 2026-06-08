#ifndef ADAPTER_DXLIB_DXLIBINPUT_H
#define ADAPTER_DXLIB_DXLIBINPUT_H

#include "core/input/InputBase.h"
#include <array>

namespace adapter {
namespace dxlib {

class DxLibInput final : public nx::core::input::InputBase {
public:
    DxLibInput() = default;
    ~DxLibInput() override = default;
    bool init() override;
    void update() override;
};

} // namespace dxlib
} // namespace adapter

#endif // !ADAPTER_DXLIB_DXLIBINPUT_H
