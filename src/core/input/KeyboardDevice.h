#ifndef CORE_INPUT_KEYBOARDDEVICE_H
#define CORE_INPUT_KEYBOARDDEVICE_H

#include "ButtonStateTracker.h"
#include "core/input/InputState.h"

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

} // namespace input
} // namespace core
} // namespace nx

#endif // CORE_INPUT_KEYBOARDDEVICE_H
