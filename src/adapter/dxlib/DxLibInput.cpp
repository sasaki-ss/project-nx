#include "adapter/dxlib/DxLibInput.h"

#include <DxLib.h>

using nx::core::input::Key;
using nx::core::input::Mouse;

struct KeyMapping {
	Key core_key;
	int dx_key;
};

struct MouseMapping {
	Mouse core_mouse;
	int dx_mouse;
};

static constexpr int DX_KEY_NUM_ALL = 256;
static constexpr int REGISTERED_KEY_COUNT = static_cast<int>(Key::Count);
static constexpr std::array<KeyMapping, REGISTERED_KEY_COUNT> KEY_MAPPINGS = { {
	{Key::A, KEY_INPUT_A},
	{Key::B, KEY_INPUT_B},
	{Key::C, KEY_INPUT_C},
	{Key::D, KEY_INPUT_D},
	{Key::E, KEY_INPUT_E},
	{Key::F, KEY_INPUT_F},
	{Key::G, KEY_INPUT_G},
	{Key::H, KEY_INPUT_H},
	{Key::I, KEY_INPUT_I},
	{Key::J, KEY_INPUT_J},
	{Key::K, KEY_INPUT_K},
	{Key::L, KEY_INPUT_L},
	{Key::M, KEY_INPUT_M},
	{Key::N, KEY_INPUT_N},
	{Key::O, KEY_INPUT_O},
	{Key::P, KEY_INPUT_P},
	{Key::Q, KEY_INPUT_Q},
	{Key::R, KEY_INPUT_R},
	{Key::S, KEY_INPUT_S},
	{Key::T, KEY_INPUT_T},
	{Key::U, KEY_INPUT_U},
	{Key::V, KEY_INPUT_V},
	{Key::W, KEY_INPUT_W},
	{Key::X, KEY_INPUT_X},
	{Key::Y, KEY_INPUT_Y},
	{Key::Z, KEY_INPUT_Z},
	{Key::Space, KEY_INPUT_SPACE},
	{Key::Enter, KEY_INPUT_RETURN},
	{Key::Esc, KEY_INPUT_ESCAPE},
	{Key::ArrowUp,KEY_INPUT_UP},
	{Key::ArrowDown, KEY_INPUT_DOWN},
	{Key::ArrowLeft, KEY_INPUT_LEFT},
	{Key::ArrowRight, KEY_INPUT_RIGHT},
	{Key::LShift, KEY_INPUT_LSHIFT},
	{Key::RShift, KEY_INPUT_RSHIFT},
	{Key::LCtrl, KEY_INPUT_LCONTROL},
	{Key::RCtrl, KEY_INPUT_RCONTROL},
} };

static constexpr int REGISTERED_MOUSE_COUNT = static_cast<int>(Mouse::Count);
static constexpr std::array<MouseMapping, REGISTERED_MOUSE_COUNT> MOUSE_MAPPINGS = { {
	{Mouse::Left, MOUSE_INPUT_LEFT},
	{Mouse::Right, MOUSE_INPUT_RIGHT},
	{Mouse::Mid, MOUSE_INPUT_MIDDLE},
	{Mouse::Exp1, MOUSE_INPUT_4},
	{Mouse::Exp2, MOUSE_INPUT_5},
} };

namespace adapter {
namespace dxlib {

bool DxLibInput::init() {
	for (const auto& key_map : KEY_MAPPINGS) {
		key_state.try_emplace(key_map.core_key, false);
	}

	return true;
}

void DxLibInput::update() {
	// キーボード
	std::array<char, DX_KEY_NUM_ALL> key_state_buffer{};
	GetHitKeyStateAll(key_state_buffer.data());

	for (const auto& key_map : KEY_MAPPINGS) {
		bool is_pressed = key_state_buffer.at(key_map.dx_key) != 0;
		key_state[key_map.core_key] = is_pressed;
	}

	// マウス
	GetMousePoint(&mouse_point.x, &mouse_point.y);
	int mouse_input = GetMouseInput();
	for (const auto& mouse_map : MOUSE_MAPPINGS) {
		bool is_pressed = (mouse_input & mouse_map.dx_mouse) != 0;
		mouse_state[mouse_map.core_mouse] = is_pressed;
	}
}

}
}