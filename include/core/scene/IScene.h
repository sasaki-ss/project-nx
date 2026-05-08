#ifndef CORE_SCENE_INTERFACE_SCENE
#define CORE_SCENE_INTERFACE_SCENE

namespace nx{
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
	virtual void update() = 0;
	virtual void draw() = 0;
};

}
}
}

#endif // !CORE_SCENE_INTERFACE_SCENE
