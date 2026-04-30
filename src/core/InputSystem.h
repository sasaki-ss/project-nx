#ifndef CORE_OBJECT_INPUTSYSTEM_H
#define CORE_OBJECT_INPUTSYSTEM_H

#include <memory>
#include <optional>

#include "InputBase.h"

namespace nx {
namespace core {
namespace input {

class InputSystem final {
public:
	typedef std::unordered_map<Key, KeyState, KeyHash> key_state_t;

	InputSystem() = default;
	~InputSystem() = default;
	bool init();
	void set_input_source(std::unique_ptr<InputBase> input_module);
	void update();
	bool get_input(Key key, KeyState state);
private:
	 auto get_key_state(Key key, key_state_t& state_map) -> std::optional<KeyState>;

	std::unique_ptr<InputBase> input_module;
	key_state_t current_state;
	key_state_t previous_state;
};


}
}
}

#endif // !CORE_OBJECT_INPUTSYSTEM_H
