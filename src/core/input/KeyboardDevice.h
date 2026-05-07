#ifndef CORE_INPUT_KEYBOARDDEVICE_H
#define CORE_INPUT_KEYBOARDDEVICE_H

#include "core/input/InputState.h"
#include "ButtonStateTracker.h"

namespace nx {
namespace core {
namespace input {

class KeyboardDevice {
public:
	KeyboardDevice() = default;
	~KeyboardDevice() = default;
	bool init();
	void update(const ButtonStateTracker<Key, KeyHash>::raw_state_t& raw_state);

	bool get_input(Key key, InputState state);
	
private:
	ButtonStateTracker<Key, KeyHash> btn_tracker;
};

}
}
}

#endif // CORE_INPUT_KEYBOARDDEVICE_H
