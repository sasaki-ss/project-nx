# nx::core::scene::SceneManager::~SceneManager

## シグネチャ
```cpp
~SceneManager();
```

## 概要
シーン管理を破棄します。
破棄の前に `end` を呼び、積まれているシーンの終了処理を行います。`end` を呼び済みの場合は何もしません。
