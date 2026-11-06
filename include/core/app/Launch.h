#ifndef CORE_APP_LAUNCH_H
#define CORE_APP_LAUNCH_H

#include "core/app/IBackend.h"
#include "core/object/Component.h"

namespace nx {
namespace core {
namespace app {

#ifndef NDEBUG
void launch(int argc, char** argv, object::Component& component, IBackend& backend);
#else
inline void launch(int, char**, object::Component&, IBackend& backend) {
    backend.apply_before_init(false);
}
#endif

} // namespace app
} // namespace core
} // namespace nx

#endif // !CORE_APP_LAUNCH_H
