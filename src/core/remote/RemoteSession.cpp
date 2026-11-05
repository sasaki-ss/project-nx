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
    inbox(std::make_shared<Inbox>()),
    capture(std::move(screen_capture)),
    processor(remote_input, *capture, write_reply_line),
    reader(read_lines, inbox) {
}

RemoteSession::~RemoteSession() {
    bool has_read_all = false;
    {
        std::lock_guard<std::mutex> lock(inbox->mutex);
        has_read_all = inbox->is_end_of_input;
    }
    // 標準入力を待っている読み取りは止められないため、読み終えていなければ切り離し、プロセスの終了に任せる
    if (has_read_all) {
        reader.join();
    } else {
        reader.detach();
    }
}

bool RemoteSession::begin_frame() {
    std::deque<std::string> received;
    bool has_read_all = false;
    {
        std::lock_guard<std::mutex> lock(inbox->mutex);
        received.swap(inbox->lines);
        has_read_all = inbox->is_end_of_input;
    }

    for (std::string& line : received) {
        processor.push_line(std::move(line));
    }
    if (has_read_all) {
        processor.push_end_of_input();
    }

    return processor.begin_frame();
}

void RemoteSession::end_frame() {
    processor.end_frame();
}

void RemoteSession::read_lines(std::shared_ptr<Inbox> shared_inbox) {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::lock_guard<std::mutex> lock(shared_inbox->mutex);
        shared_inbox->lines.push_back(line);
    }

    std::lock_guard<std::mutex> lock(shared_inbox->mutex);
    shared_inbox->is_end_of_input = true;
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
