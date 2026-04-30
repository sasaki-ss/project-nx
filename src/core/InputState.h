#ifndef CORE_INPUT_INPUTSTATE_H
#define CORE_INPUT_INPUTSTATE_H

#include <type_traits>

namespace nx {
namespace core {
namespace input {

enum class Key {
	A,
	D,
	S,
	W,
};

enum class KeyState {
	Pressed, 
	Down,
	Released
};

struct KeyHash {
	std::size_t operator()(Key key)const noexcept {
		using Underlying = std::underlying_type_t<Key>;
		return static_cast<std::size_t>(static_cast<Underlying>(key));
	}
};

}
}
}

#endif // !CORE_INPUT_INPUTSTATE_H
