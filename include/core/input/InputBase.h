#ifndef CORE_INPUT_INPUTBASE_H
#define CORE_INPUT_INPUTBASE_H

#include <unordered_map>

#include "InputState.h"

namespace nx {
namespace core {
namespace input {

class InputBase {
public:
    InputBase() = default;
    virtual ~InputBase() = default;
    virtual bool init() = 0;
    virtual void update() = 0;
    auto get_key_state() const -> const std::unordered_map<Key, bool, KeyHash>& {
        return key_state;
    }
    auto get_mouse_state() const -> const std::unordered_map<Mouse, bool, MouseHash>& {
        return mouse_state;
    }
    auto get_mouse_point() const -> const MousePoint& {
        return mouse_point;
    }
    auto get_mouse_wheel() const -> int {
        return mouse_wheel;
    }

protected:
    std::unordered_map<Key, bool, KeyHash> key_state;

    MousePoint mouse_point;
    std::unordered_map<Mouse, bool, MouseHash> mouse_state;
    // 前の update から回った量 (ノッチの数)。奥へ回すと正
    int mouse_wheel = 0;
};

} // namespace input
} // namespace core
} // namespace nx

#endif // CORE_INPUT_INPUTBASE_H
