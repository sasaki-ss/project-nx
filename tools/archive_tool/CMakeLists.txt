cmake_minimum_required(VERSION 3.20)

project(archive_tool CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(archive_tool main.cpp)

target_compile_options(archive_tool PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/utf-8>)
