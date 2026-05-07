# nx::core::input::InputBase::get_key_state

## シグネチャ
```cpp
const std::unordered_map<Key, bool, KeyHash>& get_key_state() const;
```

## 概要
キー状態マップを参照します。

## サンプルコード
```cpp
using nx::core::input::InputBase;
using nx::core::input::Key;

void dump_space(const InputBase& input) {
    const auto& keys = input.get_key_state();
    auto it = keys.find(Key::Space);
    // 見つかったら押下状態を参照する
    (void)it;
}
```
