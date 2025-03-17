# Auto-Sync Tool

Công cụ tự động đồng bộ file và commit code cho workspace.

## Cách tự động khởi động Auto-Sync

### Phương pháp 1: Sử dụng VSCode Tasks (tự động)
Workspace đã được cấu hình để tự động chạy Auto-Sync khi mở. Chỉ cần mở thư mục này bằng VSCode, công cụ sẽ tự động khởi động.

### Phương pháp 2: Sử dụng script khởi động (nếu phương pháp 1 không hoạt động)
```bash
# Trên macOS/Linux
./start-workspace.sh

# Hoặc trên Windows
./start-workspace.bat
```

### Phương pháp 3: Khởi động thủ công
```bash
# Chạy trong terminal
python3 automatic.py
```

## Các lệnh hỗ trợ

Thêm các lệnh sau vào file của bạn để kích hoạt tính năng:

- `//sync now`: Đồng bộ file đến vị trí đích (theo comment dòng đầu tiên)
- `//commit.`: Commit và push lên nhánh hiện tại
- `//commit tên_nhánh.`: Commit và push lên nhánh được chỉ định
- `//status`: Kiểm tra trạng thái đồng bộ file

## Lưu ý

- Dòng đầu tiên của file phải chứa đường dẫn đích (ví dụ: `//đường/dẫn/đến/file`)
- Log hoạt động được lưu trong `autosync_log.json`

/* AUTO-SYNC STATUS START */
/* ✅ ✅ Đã đồng bộ đến /Users/astrelix/Documents/HSG11/Auto-Sync Tool */
/* ⏱️ Thời gian: 02:30:27 18/03/2025 */
/* AUTO-SYNC STATUS END */
