#include "RemoteSession.h"

#include "core/remote/Remote.h"

#include <iostream>
#include <utility>

namespace nx {
namespace core {
namespace remote {

#ifndef NDEBUG

static std::unique_ptr<RemoteSession> current_session;

static void write_reply_line(const std::string& line) {
    std::cout << (line + '\n') << std::flush;
}

RemoteSession::RemoteSession(RemoteInput& remote_input, std::unique_ptr<graphics::IScreenCapture> screen_capture) :
    capture(std::move(screen_capture)),
    processor(remote_input, *capture, write_reply_line) {
}

bool RemoteSession::begin_frame() {
    StdinReader::Received received = reader.take_received();
    for (std::string& line : received.lines) {
        processor.push_line(std::move(line));
    }
    if (received.is_end_of_input) {
        processor.push_end_of_input();
    }

    return processor.begin_frame();
}

void RemoteSession::end_frame() {
    processor.end_frame();
}

bool start(RemoteInput& remote_input, std::unique_ptr<graphics::IScreenCapture> screen_capture) {
    if (current_session || !screen_capture) {
        return false;
    }

    current_session = std::make_unique<RemoteSession>(remote_input, std::move(screen_capture));
    return true;
}

bool begin_frame() {
    if (!current_session) {
        return true;
    }

    return current_session->begin_frame();
}

void end_frame() {
    if (current_session) {
        current_session->end_frame();
    }
}

#endif

} // namespace remote
} // namespace core
} // namespace nx
