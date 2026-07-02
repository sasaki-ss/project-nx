cmake_minimum_required(VERSION 3.20)

# nx ライブラリ本体 (src 配下のみをビルドする)
project(nx LANGUAGES CXX)

# DxLib SDK の配置場所 (ヘッダとライブラリが同一ディレクトリ)
set(DXLIB_DIR "C:/dxlib/DxLib_VC3_24f/DxLib_VC/lib" CACHE PATH "DxLib SDK directory")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# DxLib は静的ランタイム (/MT, /MTd) 前提
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(nx STATIC
    src/adapter/dxlib/DxLibDrawHelper.cpp
    src/adapter/dxlib/DxLibInput.cpp
    src/core/input/InputSystem.cpp
    src/core/input/KeyboardDevice.cpp
    src/core/input/MouseDevice.cpp
    src/core/scene/SceneManager.cpp
)

target_include_directories(nx PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${DXLIB_DIR}
)

# nx.lib をルート直下に生成する ($<1:...> で構成別サブディレクトリを抑止)
set_target_properties(nx PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "$<1:${CMAKE_SOURCE_DIR}>"
)
