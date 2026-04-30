#include "InputSystem.h"

namespace nx {
namespace core {
namespace input {

bool InputSystem::init() {
	current_state[Key::A] = KeyState::Released;
	previous_state[Key::A] = KeyState::Released;
	current_state[Key::D] = KeyState::Released;
	previous_state[Key::D] = KeyState::Released;
	current_state[Key::S] = KeyState::Released;
	previous_state[Key::S] = KeyState::Released;
	current_state[Key::W] = KeyState::Released;
	previous_state[Key::W] = KeyState::Released;

	return true;
}

void InputSystem::set_input_source(std::unique_ptr<InputBase> input_module) {
	this->input_module = std::move(input_module);
	//this->input_module->init();
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

		if (state && prev_st == KeyState::Released) {
			current_state[key] = KeyState::Pressed;
		}
		else if (state && prev_st == KeyState::Pressed) {
			current_state[key] = KeyState::Down;
		}
		else if (!state && (prev_st == KeyState::Pressed || prev_st == KeyState::Down)) {
			current_state[key] = KeyState::Released;
		}

		auto cur_st = get_key_state(key, current_state);
		if (!cur_st.has_value())continue;
		previous_state[key] = *cur_st;
	}
}

bool InputSystem::get_input(Key key, KeyState state) {
	auto key_state = get_key_state(key, current_state);
	if (!key_state.has_value()) {
		return false;
	}

	if (*key_state == state) {
		return true;
	}

	return false;
}

auto InputSystem::get_key_state(Key key, key_state_t& state_map) -> std::optional<KeyState> {
	auto it = state_map.find(key);
	if (it != state_map.end()) {
		return it->second;
	}

	return std::nullopt;
}

}
}
}