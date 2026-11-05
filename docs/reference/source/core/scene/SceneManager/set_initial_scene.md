# nx::core::scene::SceneManager::set_initial_scene

## シグネチャ
```cpp
void set_initial_scene(uint32_t scene_id);
```

## 概要
`init` で最初に生成するシーンの ID を指定します。
ID は `set_scene_creator` で登録したものを使います。

## 備考
指定しない場合、`init` はシーンを積まずに成功します (仮起動)。
シーンが積まれていない間、`update` と `draw` は何もしません。
