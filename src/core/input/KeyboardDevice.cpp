#include "KeyboardDevice.h"

#include "core/input/InputState.h"

using nx::core::input::Key;

namespace nx {
namespace core {
namespace input {

bool KeyboardDevice::init() {
	btn_tracker.set_count(static_cast<int>(Key::Count));
	return btn_tracker.init();
}

void KeyboardDevice::update(const ButtonStateTracker<Key, KeyHash>::raw_state_t& raw_state) {
	btn_tracker.update(raw_state);
}

bool KeyboardDevice::get_input(Key key, InputState state) {
	auto key_state = btn_tracker.get_input_state(key);
	if (!key_state.has_value()) {
		return false;
	}

	if (*key_state == state) {
		return true;
	}

	return false;
}

}
}
}