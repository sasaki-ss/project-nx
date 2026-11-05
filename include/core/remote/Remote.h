#ifndef CORE_REMOTE_REMOTE_H
#define CORE_REMOTE_REMOTE_H

namespace nx {
namespace core {
namespace remote {

#ifndef NDEBUG
bool begin_frame();
void end_frame();
#else
inline bool begin_frame() {
    return true;
}

inline void end_frame() {
}
#endif

} // namespace remote
} // namespace core
} // namespace nx

#endif // !CORE_REMOTE_REMOTE_H
