#ifndef CORE_INPUT_BUTTONSTATETRACKER_H
#define CORE_INPUT_BUTTONSTATETRACKER_H

#include <unordered_map>
#include <optional>

#include "core/input/InputState.h"

namespace nx {
namespace core {
namespace input {

template <class T,typename Hash>
class ButtonStateTracker {
public:
	typedef std::unordered_map<T, InputState, Hash> input_state_t;
	typedef std::unordered_map<T, bool, Hash> raw_state_t;

	ButtonStateTracker() :
		count(0) {

	}

	~ButtonStateTracker() = default;
	bool init();
	void update(const raw_state_t& raw_state);
	

	void set_count(const int count) {
		this->count = count;
	}
	auto get_input_state(T kind) -> std::optional<InputState> {
		return get_input_state_impl(kind, current_state);
	}
	
private:
	int count;
	input_state_t current_state;
	input_state_t previous_state;
	auto get_input_state_impl(T kind, input_state_t& state_map)const -> std::optional<InputState>;
};

template <class T, typename Hash>
bool ButtonStateTracker<T, Hash>::init() {
	// Tは0からの連番である前提
	for (int i = 0; i < count; ++i) {
		current_state[static_cast<T>(i)] = InputState::Released;
		previous_state[static_cast<T>(i)] = InputState::Released;
	}

	return true;
}

template <class T, typename Hash>
void ButtonStateTracker<T, Hash>::update(const raw_state_t& raw_state) {
	// raw_state は管理対象の全入力を毎フレーム含む前提
	for (auto& [kind, state] : raw_state) {
		auto prev_st = get_input_state_impl(kind, previous_state);
		if (!prev_st.has_value())continue;

		if (state && prev_st == InputState::Released) {
			current_state[kind] = InputState::Pressed;
		}
		// Down継続は暗黙維持のため遷移タイミングのみ更新する
		else if (state && prev_st == InputState::Pressed) {
			current_state[kind] = InputState::Down;
		}
		else if (!state && (prev_st == InputState::Pressed || prev_st == InputState::Down)) {
			current_state[kind] = InputState::Released;
		}

		auto cur_st = get_input_state_impl(kind, current_state);
		if (!cur_st.has_value())continue;
		previous_state[kind] = *cur_st;
	}
}

template <class T, typename Hash>
auto ButtonStateTracker<T, Hash>::get_input_state_impl(T kind, input_state_t& state_map)const -> std::optional<InputState> {
	auto it = state_map.find(kind);
	if (it != state_map.end()) {
		return it->second;
	}

	return std::nullopt;
}

}
}
}

#endif // CORE_INPUT_BUTTONSTATETRACKER_H
