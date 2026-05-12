# nx::core::scene::SceneManager::update

## シグネチャ
```cpp
void update();
```

## 概要
保留中のシーン遷移を反映してから、現在シーンを更新します。
現在シーンの `update` には `SceneManager` 自身を `ISceneDirector&` として渡します。
