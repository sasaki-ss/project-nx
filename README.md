# nx
hello nx project!

## ビルド手順

### 前提

| 項目 | 内容 |
|---|---|
| コンパイラ | Visual Studio 2022 (MSVC v143) |
| ビルドツール | CMake 3.20 以上 |
| DxLib SDK | 既定パス `C:/dxlib/DxLib_VC3_24f/DxLib_VC/lib`(変更する場合は `-DDXLIB_DIR=<path>` を指定) |

### 構成

| ビルド対象 | CMake の場所 | 生成物(ルート直下) |
|---|---|---|
| nx ライブラリ本体(`src/` 配下) | `CMakeLists.txt`(ルート) | `nx.lib` |
| 動作確認環境(`sandbox/` 配下) | `sandbox/CMakeLists.txt`(独立プロジェクト) | `sandbox.exe` |

### 手順

ライブラリ → 動作確認環境の順にビルドする。`--config`(Debug / Release)は両者で揃えること。

```powershell
# 1. nx ライブラリ (nx.lib をルート直下に生成)
cmake -S . -B build
cmake --build build --config Debug

# 2. 動作確認環境 (ルート直下の nx.lib をリンクし、sandbox.exe をルート直下に生成)
cmake -S sandbox -B sandbox/build
cmake --build sandbox/build --config Debug
```
