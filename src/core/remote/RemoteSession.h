#ifndef CORE_REMOTE_REMOTESESSION_H
#define CORE_REMOTE_REMOTESESSION_H

#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "core/graphics/IScreenCapture.h"
#include "CommandProcessor.h"
#include "RemoteInput.h"

namespace nx {
namespace core {
namespace remote {

class RemoteSession {
public:
    RemoteSession(RemoteInput& remote_input, std::unique_ptr<graphics::IScreenCapture> screen_capture);
    ~RemoteSession();
    RemoteSession(const RemoteSession&) = delete;
    RemoteSession& operator=(const RemoteSession&) = delete;

    bool begin_frame();
    void end_frame();

private:
    struct Inbox {
        std::mutex mutex;
        std::deque<std::string> lines;
        bool is_end_of_input = false;
    };

    static void read_lines(std::shared_ptr<Inbox> shared_inbox);

    std::shared_ptr<Inbox> inbox;
    // processor は capture を参照するので、capture を先に作り、後に壊す
    std::unique_ptr<graphics::IScreenCapture> capture;
    CommandProcessor processor;
    std::thread reader;
};

bool start(RemoteInput& remote_input, std::unique_ptr<graphics::IScreenCapture> screen_capture);

} // namespace remote
} // namespace core
} // namespace nx

#endif // !CORE_REMOTE_REMOTESESSION_H
