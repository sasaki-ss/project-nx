"""nx の AI 操作 (--nx-remote) で起動したゲームを、Python から操作する。"""

import queue
import subprocess
import threading
from pathlib import Path

READY_TIMEOUT = 20.0
REPLY_TIMEOUT = 10.0
EXIT_TIMEOUT = 10.0

REPLY_PREFIX = "@"
REPLY_READY = "@ready"
REPLY_OK = "@ok"
REPLY_ERROR = "@error"


class RemoteError(Exception):
    pass


class RemoteGame:
    def __init__(self, process):
        self._process = process
        self._replies = queue.Queue()
        self.logs = []
        self._reader = threading.Thread(target=self._read_stdout, daemon=True)
        self._reader.start()

    @classmethod
    def launch(cls, exe_path, work_dir=None, args=(), ready_timeout=READY_TIMEOUT):
        process = subprocess.Popen(
            [str(Path(exe_path).resolve()), "--nx-remote", *args],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            cwd=work_dir,
            creationflags=subprocess.CREATE_NO_WINDOW,
            text=True,
            encoding="utf-8",
            errors="replace",
        )
        game = cls(process)
        try:
            game._expect(REPLY_READY, ready_timeout)
        except RemoteError:
            game._kill()
            raise
        return game

    def move(self, x, y, timeout=REPLY_TIMEOUT):
        self._send(f"move {x} {y}", timeout)

    def click(self, x, y, timeout=REPLY_TIMEOUT):
        self._send(f"click {x} {y}", timeout)

    def wheel(self, x, y, amount, timeout=REPLY_TIMEOUT):
        self._send(f"wheel {x} {y} {amount}", timeout)

    def press(self, timeout=REPLY_TIMEOUT):
        self._send("press", timeout)

    def release(self, timeout=REPLY_TIMEOUT):
        self._send("release", timeout)

    def drag(self, from_x, from_y, to_x, to_y, timeout=REPLY_TIMEOUT):
        self.move(from_x, from_y, timeout)
        self.press(timeout)
        self.move(to_x, to_y, timeout)
        self.release(timeout)

    def shot(self, path, timeout=REPLY_TIMEOUT):
        # ゲームは自分の作業フォルダを基準にパスを読むので、呼んだ側の基準で絶対パスにしてから送る
        self._send(f"shot {Path(path).resolve()}", timeout)

    def quit(self, timeout=EXIT_TIMEOUT):
        self._send("quit", timeout)
        try:
            code = self._process.wait(timeout)
        except subprocess.TimeoutExpired:
            self._kill()
            raise RemoteError(f"game did not exit within {timeout}s after quit") from None
        if code != 0:
            raise RemoteError(f"game exited with code {code}")
        return code

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc, tb):
        if self._process.poll() is not None:
            return
        try:
            self.quit()
        except RemoteError:
            self._kill()
            # with の中で起きた例外を、後片付けの失敗で隠さない
            if exc_type is None:
                raise

    def _read_stdout(self):
        for line in self._process.stdout:
            line = line.rstrip("\n")
            if line.startswith(REPLY_PREFIX):
                self._replies.put(line)
            else:
                self.logs.append(line)
        self._replies.put(None)

    def _send(self, command, timeout):
        if self._process.poll() is not None:
            raise RemoteError(f"game has already exited with code {self._process.returncode}")
        try:
            self._process.stdin.write(command + "\n")
            self._process.stdin.flush()
        except OSError as error:
            raise RemoteError(f"failed to send '{command}': {error}") from error
        self._expect(REPLY_OK, timeout)

    def _expect(self, expected, timeout):
        try:
            reply = self._replies.get(timeout=timeout)
        except queue.Empty:
            raise RemoteError(f"no reply within {timeout}s (expected {expected})") from None
        if reply is None:
            # 後の呼び出しも時間切れを待たずに失敗させるため、終わった印を戻しておく
            self._replies.put(None)
            raise RemoteError(f"game exited before {expected}: {self._format_last_logs()}")
        if reply == expected:
            return
        if reply.startswith(REPLY_ERROR):
            raise RemoteError(reply[len(REPLY_ERROR):].strip())
        raise RemoteError(f"unexpected reply: {reply} (expected {expected})")

    def _kill(self):
        if self._process.poll() is None:
            self._process.kill()
            self._process.wait()

    def _format_last_logs(self, count=5):
        return " | ".join(self.logs[-count:]) or "(no log)"
