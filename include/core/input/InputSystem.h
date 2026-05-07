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
	typedef std::unordered_map<Key, InputState, KeyHash> key_state_t;

	InputSystem();
	~InputSystem();
	bool init();
	bool set_input_source(std::unique_ptr<InputBase> input_module);
	void update();
	bool get_input(Key key, InputState state);
	bool get_input(Mouse mouse, InputState state);
private:
	std::unique_ptr<KeyboardDevice> keyboard_dev;
	std::unique_ptr<MouseDevice> mouse_dev;

	auto get_key_state(Key key, key_state_t& state_map) -> std::optional<InputState>;

	std::unique_ptr<InputBase> input_module;
	key_state_t current_state;
	key_state_t previous_state;
};


}
}
}

#endif // !CORE_INPUT_INPUTSYSTEM_H
