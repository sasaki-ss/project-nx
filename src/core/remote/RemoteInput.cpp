#include "RemoteInput.h"

using nx::core::input::Key;
using nx::core::input::Mouse;
using nx::core::input::MousePoint;

namespace nx {
namespace core {
namespace remote {

bool RemoteInput::init() {
    for (int i = 0; i < static_cast<int>(Key::Count); ++i) {
        key_state[static_cast<Key>(i)] = false;
    }
    for (int i = 0; i < static_cast<int>(Mouse::Count); ++i) {
        mouse_state[static_cast<Mouse>(i)] = false;
    }
    update();

    return true;
}

void RemoteInput::update() {
    mouse_point = next_mouse_point;
    mouse_state[Mouse::Left] = next_left_button;
}

void RemoteInput::set_mouse_point(const MousePoint& point) {
    next_mouse_point = point;
}

void RemoteInput::set_left_button(bool is_down) {
    next_left_button = is_down;
}

} // namespace remote
} // namespace core
} // namespace nx
