# nx::core::util::Logger
<!-- @category: class -->

## 概要

ログを標準出力へ書くクラスです。nx の各機能とゲームの両方から、共有インスタンス `logger` を通して使います。
Debug ビルド (`NDEBUG` が未定義) のときだけ出力し、Release ビルドでは何もしません。ファイルへは書きません。

## 定義

```cpp
namespace nx::core::util {

class Logger final {
public:
    template <class... Args>
    void error(LogMessage message, const Args&... args);
    template <class... Args>
    void warn(LogMessage message, const Args&... args);
    template <class... Args>
    void info(LogMessage message, const Args&... args);
    template <class... Args>
    void debug(LogMessage message, const Args&... args);

    void set_level(LogLevel new_level);
};

inline Logger logger;

}
```

## 所属レイヤー

Core

## 責務

- レベルに応じてログを標準出力へ書く
- 呼び出し元の関数・ファイル・行を、呼び出し側が書かなくても付ける
- 別スレッドから同時に書かれても、行が混ざらないようにする

## 出力形式

```
[時刻][レベル][ファイル名][クラス::関数:行]: メッセージ
[14:03:21.123][WARN][SceneManager.cpp][SceneManager::create_scene:85]: scene creator is not registered: id=3
```

- 時刻は、その日のローカル時刻をミリ秒まで出します。
- ファイル名は、パスを除いた名前です。
- 関数名からは名前空間を除き、クラス名と関数名だけを残します。名前空間は小文字、クラスは大文字で始める命名規則を前提にしています。
- ラムダの中から呼んだ場合は、そのラムダを書いた関数の名前になります。

## メンバ関数

| 名前 | 説明 |
|---|---|
| [error()](/D:/work/Project_Core/docs/reference/source/core/util/Logger/error.md) | ERROR のログを書く |
| [warn()](/D:/work/Project_Core/docs/reference/source/core/util/Logger/warn.md) | WARN のログを書く |
| [info()](/D:/work/Project_Core/docs/reference/source/core/util/Logger/info.md) | INFO のログを書く |
| [debug()](/D:/work/Project_Core/docs/reference/source/core/util/Logger/debug.md) | DEBUG のログを書く |
| [set_level()](/D:/work/Project_Core/docs/reference/source/core/util/Logger/set_level.md) | どのレベルまで出すかを設定する |

## 備考

- 関数名の取得に MSVC の `__builtin_FUNCSIG()` を使うため、MSVC 専用です。
- nx の中で出すメッセージは英語で書きます。ゲーム側のメッセージの言語は自由です。

## サンプルコード

```cpp
#include "core/util/Logger.h"

using nx::core::util::LogLevel;
using nx::core::util::logger;

void load_stage(int stage_id) {
    logger.info("load stage: id=", stage_id);

    logger.set_level(LogLevel::Debug);
    logger.debug("stage detail");
}
```

## 関連項目

- [nx::core::util::LogLevel](/D:/work/Project_Core/docs/reference/source/core/util/LogLevel.md)
- [nx::core::util::LogMessage](/D:/work/Project_Core/docs/reference/source/core/util/LogMessage.md)
