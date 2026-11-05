#include "CommandProcessor.h"

#include <optional>
#include <sstream>
#include <utility>

using nx::core::input::MousePoint;

static constexpr std::string_view REPLY_READY = "@ready";
static constexpr std::string_view REPLY_OK = "@ok";
static constexpr std::string_view REPLY_ERROR = "@error";

static constexpr std::string_view ERROR_UNKNOWN_COMMAND = "unknown command:";
static constexpr std::string_view ERROR_USAGE = "usage:";
static constexpr std::string_view ERROR_SAVE_FAILED = "failed to save:";

static bool has_no_more_args(std::istream& args) {
    std::string extra;
    return !(args >> extra);
}

static auto read_point(std::istream& args) -> std::optional<MousePoint> {
    MousePoint point{0, 0};
    if (!(args >> point.x >> point.y) || !has_no_more_args(args)) {
        return std::nullopt;
    }
    return point;
}

namespace nx {
namespace core {
namespace remote {

const CommandProcessor::Command CommandProcessor::COMMANDS[] = {
    {"move", "x y", &CommandProcessor::run_move},
    {"click", "x y", &CommandProcessor::run_click},
    {"shot", "path", &CommandProcessor::run_shot},
    {"quit", "", &CommandProcessor::run_quit},
};

CommandProcessor::CommandProcessor(RemoteInput& remote_input, graphics::IScreenCapture& screen_capture, reply_writer_t writer) :
    input(remote_input),
    capture(screen_capture),
    reply_writer(std::move(writer)) {
}

void CommandProcessor::push_line(std::string line) {
    lines.push_back(std::move(line));
}

void CommandProcessor::push_end_of_input() {
    is_end_of_input = true;
}

bool CommandProcessor::begin_frame() {
    switch (state) {
    case State::Starting:
        write_reply(REPLY_READY);
        state = State::Idle;
        break;
    case State::Releasing:
        input.set_left_button(false);
        write_reply(REPLY_OK);
        state = State::Idle;
        // 離したフレームで次の命令がボタンを押すと、離したことがゲームに伝わらない
        return true;
    case State::Stopped:
        return false;
    case State::Idle:
    case State::Shooting:
        break;
    }

    while (state == State::Idle && !lines.empty()) {
        std::string line = std::move(lines.front());
        lines.pop_front();
        run_line(line);
    }
    if (state == State::Idle && lines.empty() && is_end_of_input) {
        state = State::Stopped;
    }

    return state != State::Stopped;
}

void CommandProcessor::end_frame() {
    if (state != State::Shooting) {
        return;
    }

    if (capture.save_png(shot_path)) {
        write_reply(REPLY_OK);
    } else {
        write_error(ERROR_SAVE_FAILED, shot_path);
    }
    shot_path.clear();
    state = State::Idle;
}

void CommandProcessor::run_line(const std::string& line) {
    std::istringstream args(line);
    std::string name;
    if (!(args >> name)) {
        return;
    }

    for (const Command& command : COMMANDS) {
        if (command.name != name) {
            continue;
        }
        if (!(this->*command.run)(args)) {
            std::string usage(command.name);
            if (!command.usage.empty()) {
                usage.append(" ").append(command.usage);
            }
            write_error(ERROR_USAGE, usage);
        }
        return;
    }

    write_error(ERROR_UNKNOWN_COMMAND, name);
}

bool CommandProcessor::run_move(std::istream& args) {
    auto point = read_point(args);
    if (!point) {
        return false;
    }

    input.set_mouse_point(*point);
    write_reply(REPLY_OK);
    return true;
}

bool CommandProcessor::run_click(std::istream& args) {
    auto point = read_point(args);
    if (!point) {
        return false;
    }

    input.set_mouse_point(*point);
    input.set_left_button(true);
    state = State::Releasing;
    return true;
}

bool CommandProcessor::run_shot(std::istream& args) {
    std::string path;
    std::getline(args >> std::ws, path);
    if (path.empty()) {
        return false;
    }

    shot_path = std::move(path);
    state = State::Shooting;
    return true;
}

bool CommandProcessor::run_quit(std::istream& args) {
    if (!has_no_more_args(args)) {
        return false;
    }

    write_reply(REPLY_OK);
    state = State::Stopped;
    return true;
}

void CommandProcessor::write_reply(std::string_view line) {
    reply_writer(std::string(line));
}

void CommandProcessor::write_error(std::string_view reason, std::string_view detail) {
    std::string line(REPLY_ERROR);
    line.append(" ").append(reason).append(" ").append(detail);
    write_reply(line);
}

} // namespace remote
} // namespace core
} // namespace nx
