#include "core/scene/SceneManager.h"

#include "core/Logger.h"
#include "core/object/Component.h"
#include "core/scene/IScene.h"

using nx::core::object::Component;

namespace nx {
namespace core {
namespace scene {

class DummyScene final : public IScene {
public:
    DummyScene(object::Component* comp) :
        IScene(comp) {
    }

    ~DummyScene() override = default;
    bool init() override {
        return true;
    }
    void end() override {
    }
    void update(ISceneDirector* scene_director) override {
        std::cout << "update now" << std::endl;
        // ログを表示
    }
    void draw() override {
        // ログを表示
        std::cout << "draw now" << std::endl;
    }
};

SceneManager::SceneManager(Component* component) :
    component(component) {
}

SceneManager::~SceneManager() {
}

bool SceneManager::init() {
    auto scene = std::make_unique<DummyScene>(component);
    if (!scene->init()) {
        return false;
    }

    scenes.push(std::move(scene));
    return true;
}

void SceneManager::end() {
    while (!scenes.empty()) {
        scenes.top()->end();
        scenes.pop();
    }
}

void SceneManager::update() {
    scene_change_commit();

    scenes.top()->update(this);
}

void SceneManager::draw() {
    scenes.top()->draw();
}

void SceneManager::set_scene_creator(uint32_t scene_id, scene_creator_t scene_creator) {
    auto [it, result] = scene_creators.try_emplace(scene_id, std::move(scene_creator));
    if (!result) {
        // ログを入れる
    }
}

void SceneManager::open(uint32_t scene_id) {
    this->scene_change(scene_id, SceneChangeMode::Push);
}

void SceneManager::go_to(uint32_t scene_id) {
    this->scene_change(scene_id, SceneChangeMode::Reset);
}

void SceneManager::back() {
    scene_change(SceneChangeMode::Pop);
}

void SceneManager::scene_change(uint32_t scene_id, SceneChangeMode mode) {
    PendingSceneChange tmp;
    if (mode != SceneChangeMode::Pop) {
        tmp.scene_id = scene_id;
    }
    tmp.mode = mode;
    pending_info = tmp;
}

void SceneManager::scene_change(SceneChangeMode mode) {
    if (mode != SceneChangeMode::Pop) {
        // ログを入れる
        return;
    }

    PendingSceneChange tmp;
    tmp.mode = mode;
    pending_info = tmp;
}

void SceneManager::scene_change_commit() {
    if (!pending_info) {
        return;
    }

    auto& info = pending_info.value();
    switch (info.mode) {
    case SceneChangeMode::Pop:
        commit_pop();
        break;
    case SceneChangeMode::Reset:
        if (!commit_reset(info.scene_id)) {
            // ログを入れる
        }
        break;
    case SceneChangeMode::Push:
        if (!commit_push(info.scene_id)) {
            // ログを入れる
        }
        break;
    default:
        // ログを入れる
        break;
    }

    pending_info.reset();
}

auto SceneManager::create_scene(uint32_t scene_id) -> std::unique_ptr<IScene> {
    auto scene_creator = scene_creators.find(scene_id);
    if (scene_creator == scene_creators.end()) {
        // ログを入れる
        return nullptr;
    }

    auto scene = scene_creator->second(component);
    if (!scene->init()) {
        // ログを入れる
        return nullptr;
    }

    return scene;
}

void SceneManager::commit_pop() {
    if (scenes.size() > 1) {
        scenes.top()->end();
        scenes.pop();
    }
}
bool SceneManager::commit_push(uint32_t scene_id) {
    auto scene = create_scene(scene_id);
    if (scene == nullptr) {
        return false;
    }

    scenes.push(std::move(scene));
    return true;
}
bool SceneManager::commit_reset(uint32_t scene_id) {
    auto scene = create_scene(scene_id);
    if (scene == nullptr) {
        return false;
    }

    while (!scenes.empty()) {
        scenes.top()->end();
        scenes.pop();
    }
    scenes.push(std::move(scene));

    return true;
}

} // namespace scene
} // namespace core
} // namespace nx