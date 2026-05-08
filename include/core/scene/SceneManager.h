#ifndef CORE_SCENE_SCENE_MANAGER_H
#define CORE_SCENE_SCENE_MANAGER_H

#include <functional>
#include <memory>
#include <optional>
#include <stack>
#include <unordered_map>
#include "ISceneDirector.h"

namespace nx {
namespace core {
namespace object {
class Component;
};

namespace scene {

class IScene;

class SceneManager final : public ISceneDirector {
public:
	SceneManager(object::Component* component);
	~SceneManager();
	bool init();
	void end();
	void update();
	void draw();

	void open(uint32_t scene_id)override;
	void go_to(uint32_t scene_id)override;
	void back()override;
	void scene_change(uint32_t scene_id, SceneChangeMode mode)override;
	void scene_change(SceneChangeMode mode)override;
	void set_scene_creator(uint32_t scene_id, scene_creator_t scene_creator)override;
private:
	struct PendingSceneChange {
		SceneChangeMode mode;
		uint32_t scene_id;
	};

	std::unordered_map<uint32_t, scene_creator_t> scene_creators;
	std::stack<std::unique_ptr<IScene>> scenes;
	std::optional<PendingSceneChange> pending_info;
	object::Component* component;

	auto create_scene(uint32_t scene_id) -> std::unique_ptr<IScene>;
	void scene_change_commit();
	void commit_pop();
	bool commit_push(uint32_t scene_id);
	bool commit_reset(uint32_t scene_id);
};

}
}
}

#endif // !CORE_SCENE_SCENE_MANAGER_H
