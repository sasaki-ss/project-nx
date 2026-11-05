# nx::core::util::LogLevel
<!-- @category: enum class -->

## 概要

ログの重要度を表す列挙型です。上にあるものほど重要です。

## 定義

```cpp
namespace nx::core::util {

enum class LogLevel {
    Error,
    Warn,
    Info,
    Debug
};

}
```

## 列挙子

| 名前 | 説明 |
|---|---|
| Error | エラー |
| Warn | 警告 |
| Info | 通常の情報。既定ではここまで出力する |
| Debug | 調べるときだけ見たい詳細。既定では出力しない |

## 関連項目

- [nx::core::util::Logger](/D:/work/Project_Core/docs/reference/source/core/util/Logger.md)
