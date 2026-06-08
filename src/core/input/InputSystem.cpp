#include "core/input/InputSystem.h"

#include "KeyboardDevice.h"
#include "MouseDevice.h"

namespace nx {
namespace core {
namespace input {

InputSystem::InputSystem() = default;
InputSystem::~InputSystem() = default;

bool InputSystem::init() {
    keyboard_dev = std::make_unique<KeyboardDevice>();
    mouse_dev = std::make_unique<MouseDevice>();

    if (keyboard_dev->init() == false) {
        return false;
    }
    if (mouse_dev->init() == false) {
        return false;
    }

    return true;
}

bool InputSystem::set_input_source(std::unique_ptr<InputBase> input_module) {
    if (!input_module) {
        return false;
    }
    this->input_module = std::move(input_module);
    return this->input_module->init();
}

void InputSystem::update() {
    if (!input_module) {
        return;
    }

    input_module->update();
    keyboard_dev->update(input_module->get_key_state());
    mouse_dev->update(input_module->get_mouse_state());
}

bool InputSystem::get_input(Key key, InputState state) {
    if (!keyboard_dev) {
        return false;
    }

    return keyboard_dev->get_input(key, state);
}

bool InputSystem::get_input(Mouse mouse, InputState state) {
    if (!mouse_dev) {
        return false;
    }

    return mouse_dev->get_input(mouse, state);
}

auto InputSystem::get_mouse_point() -> std::optional<MousePoint> {
    if (!input_module) {
        return std::nullopt;
    }

    return input_module->get_mouse_point();
}

} // namespace input
} // namespace core
} // namespace nx
