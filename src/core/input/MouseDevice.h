#ifndef CORE_INPUT_MOUSEDEVICE_H
#define CORE_INPUT_MOUSEDEVICE_H

#include "ButtonStateTracker.h"
#include "core/input/InputState.h"

namespace nx {
namespace core {
namespace input {

class MouseDevice {
public:
    MouseDevice() = default;
    ~MouseDevice() = default;
    bool init();
    void update(const ButtonStateTracker<Mouse, MouseHash>::raw_state_t& raw_state);

    bool get_input(Mouse mouse, InputState state);

private:
    ButtonStateTracker<Mouse, MouseHash> btn_tracker;
};

} // namespace input
} // namespace core
} // namespace nx

#endif // CORE_INPUT_MOUSEDEVICE_H
