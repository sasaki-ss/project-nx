#include "DxLibInput.h"

#include <DxLib.h>

using nx::core::input::Key;

static constexpr int KEY_NUM_ALL = 256;

namespace adapter {
namespace dxlib {

bool DxLibInput::init() {
	return true;
}

void DxLibInput::update() {
	std::array<char, KEY_NUM_ALL> key_state_buffer{};
	GetHitKeyStateAll(key_state_buffer.data());

	update_key_state(Key::A, key_state_buffer.at(KEY_INPUT_A));
	update_key_state(Key::D, key_state_buffer.at(KEY_INPUT_D));
	update_key_state(Key::S, key_state_buffer.at(KEY_INPUT_S));
	update_key_state(Key::W, key_state_buffer.at(KEY_INPUT_W));
}


void DxLibInput::update_key_state(Key key, int state) {
	bool is_pressed = false;
	if (state == 1) {
		is_pressed = true;
	}

	auto it = key_state.find(key);
	if (it == key_state.end()) {
		key_state.try_emplace(key, is_pressed);
		return;
	}

	it->second = is_pressed;
}

}
}