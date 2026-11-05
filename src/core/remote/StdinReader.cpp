#include "StdinReader.h"

#include <iostream>

namespace nx {
namespace core {
namespace remote {

#ifndef NDEBUG

StdinReader::StdinReader() :
    inbox(std::make_shared<Inbox>()),
    reader(read_lines, inbox) {
}

StdinReader::~StdinReader() {
    bool has_read_all = false;
    {
        std::lock_guard<std::mutex> lock(inbox->mutex);
        has_read_all = inbox->received.is_end_of_input;
    }
    // 標準入力を待っている読み取りは止められないため、読み終えていなければ切り離し、プロセスの終了に任せる
    if (has_read_all) {
        reader.join();
    } else {
        reader.detach();
    }
}

auto StdinReader::take_received() -> Received {
    Received taken;
    std::lock_guard<std::mutex> lock(inbox->mutex);
    taken.lines.swap(inbox->received.lines);
    taken.is_end_of_input = inbox->received.is_end_of_input;
    return taken;
}

void StdinReader::read_lines(std::shared_ptr<Inbox> shared_inbox) {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::lock_guard<std::mutex> lock(shared_inbox->mutex);
        shared_inbox->received.lines.push_back(line);
    }

    std::lock_guard<std::mutex> lock(shared_inbox->mutex);
    shared_inbox->received.is_end_of_input = true;
}

#endif

} // namespace remote
} // namespace core
} // namespace nx
