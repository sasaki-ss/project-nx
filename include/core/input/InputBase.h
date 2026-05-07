#ifndef CORE_INPUT_INPUTBASE_H
#define CORE_INPUT_INPUTBASE_H

#include <unordered_map>

#include "InputState.h"

namespace nx {
namespace core {
namespace input {

class InputBase {
public:
	InputBase() = default;
	virtual ~InputBase() = default;
	virtual bool init() = 0;
	virtual void update() = 0;
	auto get_key_state() -> const std::unordered_map<Key, bool, KeyHash>& {
		return key_state;
	}
	auto get_mouse_state() -> const std::unordered_map<Mouse, bool, MouseHash>& {
		return mouse_state;
	}
	const MousePoint& get_mouse_point() {
		return mouse_point;
	}
protected:
	std::unordered_map<Key, bool, KeyHash> key_state;

	MousePoint mouse_point;
	std::unordered_map<Mouse, bool, MouseHash> mouse_state;
};

}
}
}

#endif // CORE_INPUT_INPUTBASE_H
