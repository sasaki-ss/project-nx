#ifndef CORE_REMOTE_COMMANDPROCESSOR_H
#define CORE_REMOTE_COMMANDPROCESSOR_H

#include <deque>
#include <functional>
#include <string>

#include "core/graphics/IScreenCapture.h"
#include "RemoteInput.h"

namespace nx {
namespace core {
namespace remote {

class CommandProcessor {
public:
    typedef std::function<void(const std::string&)> reply_writer_t;

    CommandProcessor(RemoteInput& remote_input, graphics::IScreenCapture& screen_capture, reply_writer_t reply_writer);
    void push_line(std::string line);
    void push_end_of_input();
    bool begin_frame();
    void end_frame();

private:
    RemoteInput& input;
    graphics::IScreenCapture& capture;
    reply_writer_t write_reply;

    std::deque<std::string> lines;
    bool is_end_of_input = false;
    bool is_ready_sent = false;
    bool is_release_pending = false;
    bool is_shot_pending = false;
    bool is_quit_requested = false;
    std::string shot_path;

    void run_line(const std::string& line);
};

} // namespace remote
} // namespace core
} // namespace nx

#endif // !CORE_REMOTE_COMMANDPROCESSOR_H
