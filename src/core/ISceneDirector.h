#ifndef CORE_SCENE_INTERFACE_SCENE_DIRECTOR
#define CORE_SCENE_INTERFACE_SCENE_DIRECTOR

namespace nx {
namespace core {
namespace scene {

enum class SceneChangeMode {
	Pop,
	Push,
	Reset
};

class ISceneDirector {
public:
	virtual ~ISceneDirector() = default;
	virtual void open(uint32_t scene_id) = 0;
	virtual void go_to(uint32_t scene_id) = 0;
	virtual void back() = 0;
	virtual void scene_change(uint32_t scene_id, SceneChangeMode mode) = 0;
	virtual void scene_change(SceneChangeMode mode) = 0;
};

}
}
}

#endif // !CORE_SCENE_INTERFACE_SCENE_DIRECTOR
