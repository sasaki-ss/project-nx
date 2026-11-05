#ifndef CORE_REMOTE_REMOTEINPUT_H
#define CORE_REMOTE_REMOTEINPUT_H

#include "core/input/InputBase.h"

namespace nx {
namespace core {
namespace remote {

class RemoteInput final : public input::InputBase {
public:
    RemoteInput() = default;
    ~RemoteInput() override = default;
    bool init() override;
    void update() override;

    void set_mouse_point(const input::MousePoint& point);
    void set_left_button(bool is_down);

private:
    input::MousePoint next_mouse_point{0, 0};
    bool next_left_button = false;
};

} // namespace remote
} // namespace core
} // namespace nx

#endif // !CORE_REMOTE_REMOTEINPUT_H
