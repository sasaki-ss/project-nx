# nx::core::util::Logger::debug

## シグネチャ
```cpp
template <class... Args>
void debug(LogMessage message, const Args&... args);
```

## 概要
DEBUG のログを書きます。`message` の後ろに `args` を順につなげて 1 行にします。
呼び出し元の関数・ファイル・行は、`message` が自動で受け取ります。

## 備考
既定では出力されません。`set_level(LogLevel::Debug)` で出力されるようになります。
Release ビルドでは何もしません。
