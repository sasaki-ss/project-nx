#include "core/app/Launch.h"

#include <memory>
#include <string_view>
#include <utility>

#include "core/remote/RemoteInput.h"
#include "core/remote/RemoteSession.h"
#include "core/util/Logger.h"

namespace nx {
namespace core {
namespace app {

#ifndef NDEBUG

static constexpr std::string_view OPTION_PREFIX = "--nx-";
static constexpr std::string_view OPTION_REMOTE = "--nx-remote";

static bool has_option(int argc, char** argv, std::string_view name) {
    for (int i = 1; i < argc; ++i) {
        if (std::string_view(argv[i]) == name) {
            return true;
        }
    }
    return false;
}

static void warn_unknown_options(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        const std::string_view option = argv[i];
        if (option.starts_with(OPTION_PREFIX) && option != OPTION_REMOTE) {
            util::logger.warn("Unknown nx option is ignored: ", option);
        }
    }
}

void launch(int argc, char** argv, object::Component& component, IBackend& backend) {
    warn_unknown_options(argc, argv);

    // 窓を隠した後で命令を受けられないと分かると、誰も操作できない見えないゲームが残るので、撮影の実装を先に作る
    std::unique_ptr<graphics::IScreenCapture> capture;
    if (has_option(argc, argv, OPTION_REMOTE)) {
        capture = backend.make_screen_capture();
        if (!capture) {
            util::logger.error("Remote control is disabled because the backend made no screen capture.");
        }
    }

    const bool is_remote_enabled = capture != nullptr;
    backend.apply_before_init(is_remote_enabled);
    if (!is_remote_enabled) {
        return;
    }

    auto remote_input_owner = std::make_unique<remote::RemoteInput>();
    remote::RemoteInput& remote_input = *remote_input_owner;
    component.input().set_input_source(std::move(remote_input_owner));
    if (!remote::start(remote_input, std::move(capture))) {
        util::logger.error("Remote control is already running. launch must be called only once.");
    }
}

#endif

} // namespace app
} // namespace core
} // namespace nx
