#ifndef CORE_REMOTE_REMOTESESSION_H
#define CORE_REMOTE_REMOTESESSION_H

#include <memory>

#include "core/graphics/IScreenCapture.h"
#include "CommandProcessor.h"
#include "RemoteInput.h"
#include "StdinReader.h"

namespace nx {
namespace core {
namespace remote {

class RemoteSession {
public:
    RemoteSession(RemoteInput& remote_input, std::unique_ptr<graphics::IScreenCapture> screen_capture);

    bool begin_frame();
    void end_frame();

private:
    // processor は capture を参照するので、capture を先に作り、後に壊す
    std::unique_ptr<graphics::IScreenCapture> capture;
    CommandProcessor processor;
    StdinReader reader;
};

bool start(RemoteInput& remote_input, std::unique_ptr<graphics::IScreenCapture> screen_capture);

} // namespace remote
} // namespace core
} // namespace nx

#endif // !CORE_REMOTE_REMOTESESSION_H
