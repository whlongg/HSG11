#!/bin/bash

# Bắt đầu script auto-sync trong nền
cd "$(dirname "$0")"
python3 automatic.py &

# Mở VSCode trong thư mục hiện tại
code .

# Lưu ý: Hãy chạy chmod +x start-workspace.sh để làm cho script có thể thực thi
