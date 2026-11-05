#include "core/util/Logger.h"

#include <cctype>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

namespace nx {
namespace core {
namespace util {

#ifndef NDEBUG

static constexpr std::string_view CALLING_CONVENTIONS[] = {"__cdecl ", "__stdcall ", "__thiscall ", "__fastcall ", "__vectorcall "};
static constexpr std::string_view LAMBDA_MARKER = "::<lambda_";
static constexpr std::string_view CALL_OPERATOR = "operator ()";

static const char* get_level_text(LogLevel level) {
    switch (level) {
    case LogLevel::Error:
        return "ERROR";
    case LogLevel::Warn:
        return "WARN";
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Debug:
        return "DEBUG";
    }
    return "UNKNOWN";
}

static std::string make_time_text() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t seconds = std::chrono::system_clock::to_time_t(now);
    const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;

    std::tm local_time{};
    localtime_s(&local_time, &seconds);

    std::ostringstream text;
    text << std::put_time(&local_time, "%H:%M:%S") << '.' << std::setw(3) << std::setfill('0') << milliseconds;
    return text.str();
}

static std::string_view make_file_name(std::string_view path) {
    const auto separator = path.find_last_of("\\/");
    if (separator == std::string_view::npos) {
        return path;
    }
    return path.substr(separator + 1);
}

// __builtin_FUNCSIG() は「戻り値 呼び出し規約 名前空間::クラス::関数(引数)」の形なので、呼び出し規約の後ろから名前を切り出す
static std::string_view find_qualified_name(std::string_view signature) {
    std::size_t name_start = 0;
    for (const auto convention : CALLING_CONVENTIONS) {
        const auto position = signature.find(convention);
        if (position != std::string_view::npos) {
            name_start = position + convention.size();
            break;
        }
    }

    const auto lambda = signature.find(LAMBDA_MARKER, name_start);
    if (lambda != std::string_view::npos) {
        return signature.substr(name_start, lambda - name_start);
    }

    int template_depth = 0;
    for (auto i = name_start; i < signature.size(); ++i) {
        if (signature.compare(i, CALL_OPERATOR.size(), CALL_OPERATOR) == 0) {
            i += CALL_OPERATOR.size() - 1;
        } else if (signature[i] == '<') {
            ++template_depth;
        } else if (signature[i] == '>') {
            --template_depth;
        } else if (signature[i] == '(' && template_depth == 0) {
            return signature.substr(name_start, i - name_start);
        }
    }
    return signature.substr(name_start);
}

// 名前空間は小文字、クラスは大文字で始まる命名規則を前提に、クラスと関数名だけを残す
static std::string make_function_name(std::string_view signature) {
    const auto qualified_name = find_qualified_name(signature);

    std::vector<std::string_view> parts;
    int template_depth = 0;
    std::size_t part_start = 0;
    for (std::size_t i = 0; i < qualified_name.size(); ++i) {
        if (qualified_name[i] == '<') {
            ++template_depth;
        } else if (qualified_name[i] == '>') {
            --template_depth;
        } else if (template_depth == 0 && qualified_name.compare(i, 2, "::") == 0) {
            parts.push_back(qualified_name.substr(part_start, i - part_start));
            part_start = i + 2;
            ++i;
        }
    }
    parts.push_back(qualified_name.substr(part_start));

    std::string name;
    for (std::size_t i = 0; i < parts.size(); ++i) {
        const auto part = parts[i].substr(0, parts[i].find('<'));
        const bool is_last = (i + 1 == parts.size());
        const bool is_class = !part.empty() && std::isupper(static_cast<unsigned char>(part[0]));
        if (!is_last && !is_class) {
            continue;
        }

        if (!name.empty()) {
            name += "::";
        }
        name += part;
    }
    return name;
}

void Logger::output(LogLevel message_level, const LogMessage& message, const std::string& body) {
    std::ostringstream line;
    line << '[' << make_time_text() << "][" << get_level_text(message_level) << "][" << make_file_name(message.file) << "]["
         << make_function_name(message.function) << ':' << message.line << "]: " << body;

    std::lock_guard<std::mutex> lock(output_mutex);
    std::cout << line.str() << std::endl;
}

#endif

} // namespace util
} // namespace core
} // namespace nx
