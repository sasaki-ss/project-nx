# nx::core::remote

## 概要

AI がゲームを操作するための Core レイヤーの API 群です。AI からの命令を標準入力で受け取り、ゲームのループに反映します。Debug ビルドでだけ動きます。

AI 操作は、`--nx-remote` を付けて起動し、main で [launch](/D:/work/Project_Core/docs/reference/source/core/app/launch.md) を呼んだときに有効になります。

AI 操作が有効でないとき (普段の起動) と Release ビルドでは、何もしません。

## 関数

| 名前 | 説明 |
|---|---|
| [begin_frame](/D:/work/Project_Core/docs/reference/source/core/remote/begin_frame.md) | フレームの頭で、届いている命令を反映する。終わる命令が来たら `false` |
| [end_frame](/D:/work/Project_Core/docs/reference/source/core/remote/end_frame.md) | 描き終えて画面を切り替える前に呼ぶ。撮影の命令が来ていれば保存する |

## 命令と返事

命令は標準入力に 1 行に 1 つ書きます。返事は標準出力に 1 行で返ります。

| 命令 | すること | 返事 |
|---|---|---|
| `move x y` | マウスを (x, y) へ動かす | すぐに `@ok` |
| `click x y` | (x, y) へ動かし、左ボタンを 1 フレーム押して、次のフレームで離す | 離したときに `@ok` |
| `wheel x y amount` | (x, y) へ動かし、次のフレームでだけホイールを amount ノッチ回す (奥へ回すと正)。同じフレームに届いた分は足し合わせる | すぐに `@ok` |
| `shot パス` | 次に描き終えた画面を PNG で保存する。パスは行の残り全部 (空白を含んでよい) | 保存できたら `@ok`、できなければ `@error failed to save: パス` |
| `quit` | ゲームのループを終わらせる | `@ok` |

- 最初のフレームの前に `@ready` を 1 回返す
- 命令は届いた順に処理する。`click` と `shot` が終わるまで、次の命令は待つ
- 知らない命令には `@error unknown command: 名前`、引数が合わない命令には `@error usage: 正しい書き方` を返す
- 標準入力が終わったら、`quit` と同じに扱う (返事はしない)
- 返事は `@` で始まる。ログ (`[時刻]` で始まる) と同じ標準出力に流れる

## 関連

- [nx::core::app::launch](/D:/work/Project_Core/docs/reference/source/core/app/launch.md)
- [nx::core::input](/D:/work/Project_Core/docs/reference/source/core/input/index.md)
- [nx::core::graphics::IScreenCapture](/D:/work/Project_Core/docs/reference/source/core/graphics/IScreenCapture.md)
