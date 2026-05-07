#include "core/input/InputSystem.h"

namespace nx {
namespace core {
namespace input {

bool InputSystem::init() {
	// Keyは0からの連番である前提
	int key_count = static_cast<int>(Key::Count);
	for (int i = 0; i < key_count; ++i) {
		current_state[static_cast<Key>(i)] = InputState::Released;
		previous_state[static_cast<Key>(i)] = InputState::Released;
	}

	return true;
}

bool InputSystem::set_input_source(std::unique_ptr<InputBase> input_module) {
	if (input_module == nullptr) {
		return false;
	}
	this->input_module = std::move(input_module);
	return this->input_module->init();
}

void InputSystem::update() {
	if (input_module == nullptr) {
		return;
	}

	input_module->update();
	auto key_states = input_module->get_key_state();
	for (auto& [key, state] : key_states) {
		auto prev_st = get_key_state(key, previous_state);
		if (!prev_st.has_value())continue;

		if (state && prev_st == InputState::Released) {
			current_state[key] = InputState::Pressed;
		}
		// Down継続は暗黙維持のため遷移タイミングのみ更新する
		else if (state && prev_st == InputState::Pressed) {
			current_state[key] = InputState::Down;
		}
		else if (!state && (prev_st == InputState::Pressed || prev_st == InputState::Down)) {
			current_state[key] = InputState::Released;
		}

		auto cur_st = get_key_state(key, current_state);
		if (!cur_st.has_value())continue;
		previous_state[key] = *cur_st;
	}
}

bool InputSystem::get_input(Key key, InputState state) {
	auto key_state = get_key_state(key, current_state);
	if (!key_state.has_value()) {
		return false;
	}

	if (*key_state == state) {
		return true;
	}

	return false;
}

bool InputSystem::get_input(Mouse mouse, InputState state) {
	return false;
}

auto InputSystem::get_key_state(Key key, key_state_t& state_map) -> std::optional<InputState> {
	auto it = state_map.find(key);
	if (it != state_map.end()) {
		return it->second;
	}

	return std::nullopt;
}

}
}
}