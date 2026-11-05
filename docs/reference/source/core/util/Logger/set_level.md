# nx::core::util::Logger::set_level

## シグネチャ
```cpp
void set_level(LogLevel new_level);
```

## 概要
どのレベルまで出力するかを設定します。指定したレベルと、それより重要なレベルのログが出力されます。

## 備考
既定は `LogLevel::Info` です (ERROR / WARN / INFO を出力し、DEBUG は出力しない)。
