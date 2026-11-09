# nx_remote

nx の AI 操作 (`--nx-remote`) で起動したゲームを、Python から操作する道具です。命令と返事の書式は、リファレンスの `nx::core::remote` にあります。

## 使える条件

- ゲームが main で `nx::core::app::launch` を呼び、ループで `begin_frame` / `end_frame` を呼んでいること
- ゲームが Debug ビルドであること (Release では AI 操作が無効)
- Windows と、Python 3 の標準ライブラリだけで動きます

## 使い方

```python
import sys
sys.path.append("<nx>/tools/remote")
from nx_remote import RemoteGame, RemoteError

with RemoteGame.launch("build/Debug/game.exe", work_dir="work") as game:
    game.shot("work/menu.png")
    game.click(640, 432)
    game.move(100, 200)
# with を抜けるときに quit を送り、終了コードが 0 かを確かめる
```

- 窓もコンソールも出さずに起動し、`@ready` を待ってから戻ります
- 命令はどれも返事 (`@ok`) を待ってから戻ります

## 関数

| 名前 | すること |
|---|---|
| `RemoteGame.launch(exe_path, work_dir=None, args=(), ready_timeout=20.0)` | `--nx-remote` を付けて起動し、`@ready` を待つ。`work_dir` はゲームの作業フォルダ、`args` は後ろに足す起動引数 |
| `move(x, y, timeout=10.0)` | マウスを動かす |
| `click(x, y, timeout=10.0)` | 動かして左クリックする。離したところで戻る |
| `wheel(x, y, amount, timeout=10.0)` | 動かしてホイールを amount ノッチ回す。奥へ回すと正 |
| `shot(path, timeout=10.0)` | 画面を PNG で保存する。相対パスは呼んだ側の作業フォルダを基準にする |
| `quit(timeout=10.0)` | 終わらせて、終了コードを返す |
| `logs` | `@` で始まらない行 (ログ) の一覧 |

## 失敗したとき

次の場合は `RemoteError` を投げます。

- 返事が `@error` だった (メッセージは `@error` の後ろの理由)
- 時間内に返事が来なかった
- ゲームが先に終わった (メッセージに最後のログ 5 行が付く)
- `quit` の後に終わらない、または終了コードが 0 でない

`launch` で失敗したときと、`quit` で終わらないときは、ゲームを強制終了します。

## 注意

- 座標はゲーム画面の座標 (左上が 0,0) の整数です。画面の外の座標も、そのまま `@ok` が返ります
- 命令・返事・ログは UTF-8 で読み書きします
