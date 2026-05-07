#ifndef CORE_INPUT_INPUTSYSTEM_H
#define CORE_INPUT_INPUTSYSTEM_H

#include <memory>
#include <optional>

#include "InputBase.h"

namespace nx {
namespace core {
namespace input {

class KeyboardDevice;
class MouseDevice;

class InputSystem final {
public:
	InputSystem();
	~InputSystem();
	bool init();
	bool set_input_source(std::unique_ptr<InputBase> input_module);
	void update();
	bool get_input(Key key, InputState state);
	bool get_input(Mouse mouse, InputState state);

	auto get_mouse_point() -> std::optional<MousePoint>;
private:
	std::unique_ptr<KeyboardDevice> keyboard_dev;
	std::unique_ptr<MouseDevice> mouse_dev;

	std::unique_ptr<InputBase> input_module;
};


}
}
}

#endif // !CORE_INPUT_INPUTSYSTEM_H
