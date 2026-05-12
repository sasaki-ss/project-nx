#ifndef CORE_SCENE_INTERFACE_SCENE_H
#define CORE_SCENE_INTERFACE_SCENE_H

#include "ISceneDirector.h"

namespace nx {
namespace core {
namespace object {
class Component;
};

namespace scene {

class IScene {
protected:
    object::Component* comp;

public:
    IScene(object::Component* comp) :
        comp(comp) {
    }

    virtual ~IScene() = default;
    virtual bool init() = 0;
    virtual void end() = 0;
    virtual void update(ISceneDirector* scene_director) = 0;
    virtual void draw() = 0;
};

} // namespace scene
} // namespace core
} // namespace nx

#endif // !CORE_SCENE_INTERFACE_SCENE_H
