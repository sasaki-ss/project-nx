#include "MouseDevice.h"

#include "core/input/InputState.h"

using nx::core::input::Key;

namespace nx {
namespace core {
namespace input {

bool MouseDevice::init() {
    btn_tracker.set_count(static_cast<int>(Mouse::Count));
    return btn_tracker.init();
}

void MouseDevice::update(const ButtonStateTracker<Mouse, MouseHash>::raw_state_t& raw_state) {
    btn_tracker.update(raw_state);
}

bool MouseDevice::get_input(Mouse mouse, InputState state) {
    auto key_state = btn_tracker.get_input_state(mouse);
    if (!key_state.has_value()) {
        return false;
    }

    if (*key_state == state) {
        return true;
    }

    return false;
}

} // namespace input
} // namespace core
} // namespace nx
