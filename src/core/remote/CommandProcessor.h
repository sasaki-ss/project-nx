#ifndef CORE_REMOTE_COMMANDPROCESSOR_H
#define CORE_REMOTE_COMMANDPROCESSOR_H

#include <deque>
#include <functional>
#include <istream>
#include <string>
#include <string_view>

#include "core/graphics/IScreenCapture.h"
#include "RemoteInput.h"

namespace nx {
namespace core {
namespace remote {

class CommandProcessor {
public:
    typedef std::function<void(const std::string&)> reply_writer_t;

    CommandProcessor(RemoteInput& remote_input, graphics::IScreenCapture& screen_capture, reply_writer_t writer);
    void push_line(std::string line);
    void push_end_of_input();
    bool begin_frame();
    void end_frame();

private:
    enum class State {
        Starting,
        Idle,
        Releasing,
        Shooting,
        Stopped
    };

    struct Command {
        std::string_view name;
        std::string_view usage;
        bool (CommandProcessor::*run)(std::istream& args);
    };
    static const Command COMMANDS[];

    RemoteInput& input;
    graphics::IScreenCapture& capture;
    reply_writer_t reply_writer;

    std::deque<std::string> lines;
    bool is_end_of_input = false;
    State state = State::Starting;
    std::string shot_path;

    void run_line(const std::string& line);
    bool run_move(std::istream& args);
    bool run_click(std::istream& args);
    bool run_wheel(std::istream& args);
    bool run_shot(std::istream& args);
    bool run_quit(std::istream& args);

    void write_reply(std::string_view line);
    void write_error(std::string_view reason, std::string_view detail);
};

} // namespace remote
} // namespace core
} // namespace nx

#endif // !CORE_REMOTE_COMMANDPROCESSOR_H
