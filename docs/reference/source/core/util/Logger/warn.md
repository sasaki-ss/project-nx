# nx::core::util::Logger::warn

## シグネチャ
```cpp
template <class... Args>
void warn(LogMessage message, const Args&... args);
```

## 概要
WARN のログを書きます。`message` の後ろに `args` を順につなげて 1 行にします。
呼び出し元の関数・ファイル・行は、`message` が自動で受け取ります。

## 備考
Release ビルドでは何もしません。
