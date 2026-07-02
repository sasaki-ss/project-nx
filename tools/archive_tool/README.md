# archive_tool

## ビルド方法（MSVC）

前提: CMake 3.20以降、Visual Studio 2022（C++ワークロード）がインストールされていること。

```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

ビルドが成功すると `build/Release/archive_tool.exe` が生成される。

## 実行方法

```
build/Release/archive_tool.exe <引数>
```
