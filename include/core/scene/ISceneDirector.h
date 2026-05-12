#ifndef CORE_SCENE_INTERFACE_SCENE_DIRECTOR_H
#define CORE_SCENE_INTERFACE_SCENE_DIRECTOR_H

#include <cstdint>
#include <functional>

namespace nx {
namespace core {
namespace object {
class Component;
};

namespace scene {

class IScene;

enum class SceneChangeMode {
    Pop,
    Push,
    Reset
};

class ISceneDirector {
public:
    typedef std::function<std::unique_ptr<IScene>(object::Component*)> scene_creator_t;

    virtual ~ISceneDirector() = default;
    virtual void open(uint32_t scene_id) = 0;
    virtual void go_to(uint32_t scene_id) = 0;
    virtual void back() = 0;
    virtual void scene_change(uint32_t scene_id, SceneChangeMode mode) = 0;
    virtual void scene_change(SceneChangeMode mode) = 0;
    virtual void set_scene_creator(uint32_t scene_id, scene_creator_t scene_creator) = 0;
};

} // namespace scene
} // namespace core
} // namespace nx

#endif // !CORE_SCENE_INTERFACE_SCENE_DIRECTOR_H
