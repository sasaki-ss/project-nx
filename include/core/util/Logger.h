#ifndef CORE_UTIL_LOGGER_H
#define CORE_UTIL_LOGGER_H

#include <atomic>
#include <mutex>
#include <sstream>
#include <string>
#include <string_view>

namespace nx {
namespace core {
namespace util {

enum class LogLevel {
    Error,
    Warn,
    Info,
    Debug
};

// 既定引数は呼び出し側で評価されるため、ログを呼んだ場所の関数・ファイル・行が入る
struct LogMessage {
    std::string_view text;
    const char* function;
    const char* file;
    int line;

    LogMessage(const char* message_text, const char* call_function = __builtin_FUNCSIG(), const char* call_file = __builtin_FILE(), int call_line = __builtin_LINE()) :
        text(message_text),
        function(call_function),
        file(call_file),
        line(call_line) {
    }

    LogMessage(const std::string& message_text, const char* call_function = __builtin_FUNCSIG(), const char* call_file = __builtin_FILE(), int call_line = __builtin_LINE()) :
        text(message_text),
        function(call_function),
        file(call_file),
        line(call_line) {
    }
};

class Logger final {
public:
    template <class... Args>
    void error(LogMessage message, const Args&... args) {
        write(LogLevel::Error, message, args...);
    }

    template <class... Args>
    void warn(LogMessage message, const Args&... args) {
        write(LogLevel::Warn, message, args...);
    }

    template <class... Args>
    void info(LogMessage message, const Args&... args) {
        write(LogLevel::Info, message, args...);
    }

    template <class... Args>
    void debug(LogMessage message, const Args&... args) {
        write(LogLevel::Debug, message, args...);
    }

    void set_level(LogLevel new_level) {
        level = new_level;
    }

private:
    // Release の空の中身が呼び出し側から見えていないと、関数名やファイルパスの文字列が exe に残るため、ヘッダに置く
    template <class... Args>
    void write(LogLevel message_level, const LogMessage& message, const Args&... args) {
#ifndef NDEBUG
        if (level.load() < message_level) {
            return;
        }

        std::ostringstream body;
        body << message.text;
        if constexpr (sizeof...(args) > 0) {
            (body << ... << args);
        }
        output(message_level, message, body.str());
#else
        (void)message_level;
        (void)message;
        ((void)args, ...);
#endif
    }

    void output(LogLevel message_level, const LogMessage& message, const std::string& body);

    std::atomic<LogLevel> level{LogLevel::Info};
    std::mutex output_mutex;
};

inline Logger logger;

} // namespace util
} // namespace core
} // namespace nx

#endif // !CORE_UTIL_LOGGER_H
