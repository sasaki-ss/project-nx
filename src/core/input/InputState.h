#ifndef CORE_INPUT_INPUTSTATE_H
#define CORE_INPUT_INPUTSTATE_H

#include <type_traits>

namespace nx {
namespace core {
namespace input {

enum class Key {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Space,
	Enter,
	Esc,
	ArrowUp,
	ArrowDown,
	ArrowLeft,
	ArrowRight,
	LShift,
	RShift,
	LCtrl,
	RCtrl,
	Count
};

enum class Mouse {
	Left,
	Right,
	Mid,
	Exp1,
	Exp2,
	Count
};

enum class InputState {
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

struct MouseHash {
	std::size_t operator()(Mouse mouse)const noexcept {
		using Underlying = std::underlying_type_t<Mouse>;
		return static_cast<std::size_t>(static_cast<Underlying>(mouse));
	}
};

}
}
}

#endif // !CORE_INPUT_INPUTSTATE_H
