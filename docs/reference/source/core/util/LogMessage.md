# nx::core::util::LogMessage
<!-- @category: struct -->

## 概要

ログのメッセージと、ログを呼んだ場所 (関数・ファイル・行) をまとめた構造体です。
`Logger` の各関数の最初の引数として、文字列から暗黙に作られます。呼び出し側が直接作る必要はありません。

## 定義

```cpp
namespace nx::core::util {

struct LogMessage {
    std::string_view text;
    const char* function;
    const char* file;
    int line;

    LogMessage(const char* message_text, const char* call_function = __builtin_FUNCSIG(), const char* call_file = __builtin_FILE(), int call_line = __builtin_LINE());
    LogMessage(const std::string& message_text, const char* call_function = __builtin_FUNCSIG(), const char* call_file = __builtin_FILE(), int call_line = __builtin_LINE());
};

}
```

## 備考

- 既定引数は呼び出し側で評価されるため、`call_function` / `call_file` / `call_line` には、ログを呼んだ場所が入ります。
- `text` は渡された文字列を参照するだけなので、ログの呼び出しが終わるまでしか有効ではありません。

## 関連項目

- [nx::core::util::Logger](/D:/work/Project_Core/docs/reference/source/core/util/Logger.md)
