#include "CommandProcessor.h"

#include <sstream>
#include <utility>

namespace nx {
namespace core {
namespace remote {

CommandProcessor::CommandProcessor(RemoteInput& remote_input, graphics::IScreenCapture& screen_capture, reply_writer_t reply_writer) :
    input(remote_input),
    capture(screen_capture),
    write_reply(std::move(reply_writer)) {
}

void CommandProcessor::push_line(std::string line) {
    lines.push_back(std::move(line));
}

void CommandProcessor::push_end_of_input() {
    is_end_of_input = true;
}

bool CommandProcessor::begin_frame() {
    if (!is_ready_sent) {
        write_reply("@ready");
        is_ready_sent = true;
    }
    if (is_quit_requested) {
        return false;
    }

    if (is_release_pending) {
        input.set_left_button(false);
        is_release_pending = false;
        write_reply("@ok");
        // 離したフレームで次の命令がボタンを押すと、離したことがゲームに伝わらない
        return true;
    }

    while (!lines.empty() && !is_release_pending && !is_shot_pending && !is_quit_requested) {
        std::string line = std::move(lines.front());
        lines.pop_front();
        run_line(line);
    }

    if (lines.empty() && is_end_of_input && !is_release_pending && !is_shot_pending) {
        is_quit_requested = true;
    }

    return !is_quit_requested;
}

void CommandProcessor::end_frame() {
    if (!is_shot_pending) {
        return;
    }

    if (capture.save_png(shot_path)) {
        write_reply("@ok");
    } else {
        write_reply("@error failed to save: " + shot_path);
    }
    is_shot_pending = false;
    shot_path.clear();
}

void CommandProcessor::run_line(const std::string& line) {
    std::istringstream in(line);
    std::string name;
    if (!(in >> name)) {
        return;
    }

    std::string extra;
    if (name == "move" || name == "click") {
        int x = 0;
        int y = 0;
        if (!(in >> x >> y) || (in >> extra)) {
            write_reply("@error usage: " + name + " x y");
            return;
        }
        input.set_mouse_point({x, y});
        if (name == "move") {
            write_reply("@ok");
            return;
        }
        input.set_left_button(true);
        is_release_pending = true;
        return;
    }

    if (name == "shot") {
        std::string path;
        std::getline(in >> std::ws, path);
        if (path.empty()) {
            write_reply("@error usage: shot path");
            return;
        }
        shot_path = std::move(path);
        is_shot_pending = true;
        return;
    }

    if (name == "quit") {
        if (in >> extra) {
            write_reply("@error usage: quit");
            return;
        }
        write_reply("@ok");
        is_quit_requested = true;
        return;
    }

    write_reply("@error unknown command: " + name);
}

} // namespace remote
} // namespace core
} // namespace nx
