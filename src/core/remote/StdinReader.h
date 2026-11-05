#ifndef CORE_REMOTE_STDINREADER_H
#define CORE_REMOTE_STDINREADER_H

#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace nx {
namespace core {
namespace remote {

class StdinReader {
public:
    struct Received {
        std::deque<std::string> lines;
        bool is_end_of_input = false;
    };

    StdinReader();
    ~StdinReader();
    StdinReader(const StdinReader&) = delete;
    StdinReader& operator=(const StdinReader&) = delete;

    auto take_received() -> Received;

private:
    struct Inbox {
        std::mutex mutex;
        Received received;
    };

    static void read_lines(std::shared_ptr<Inbox> shared_inbox);

    // 切り離した読み取りはこのオブジェクトより長く生きることがあるので、読み取りが触る物は共有して持つ
    std::shared_ptr<Inbox> inbox;
    std::thread reader;
};

} // namespace remote
} // namespace core
} // namespace nx

#endif // !CORE_REMOTE_STDINREADER_H
