import os
import time
import shutil
import git
import threading
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

WATCH_DIR = os.getcwd()  # Theo dõi thư mục hiện tại

def read_first_comment(file_path):
    """Đọc dòng đầu tiên để lấy đường dẫn đích"""
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            first_line = f.readline().strip()
            if first_line.startswith("//"):
                return first_line[2:].strip()  # Bỏ "//" ở đầu
    except Exception as e:
        print(f"⚠️ Lỗi đọc file {file_path}: {e}")
    return None

def remove_line(file_path, line_to_remove):
    """Xóa một dòng cụ thể trong file"""
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
        with open(file_path, "w", encoding="utf-8") as f:
            new_lines = [line for line in lines if line.strip() != line_to_remove]
            f.writelines(new_lines)
    except Exception as e:
        print(f"⚠️ Lỗi khi xóa dòng '{line_to_remove}': {e}")

def add_temporary_message(file_path, message):
    """Thêm thông báo vào file và tự động xóa sau 2s"""
    try:
        with open(file_path, "a", encoding="utf-8") as f:
            f.write(f"\n{message}\n")
        time.sleep(2)
        remove_line(file_path, message)
    except Exception as e:
        print(f"⚠️ Lỗi khi thêm thông báo: {e}")

def sync_file(file_path):
    """Đồng bộ file đến vị trí đích"""
    dest_path = read_first_comment(file_path)
    if not dest_path:
        print(f"⚠️ Không tìm thấy đường dẫn đích trong {file_path}")
        return
    dest_path = os.path.join(WATCH_DIR, dest_path)

    # Tránh copy vào chính nó
    if os.path.abspath(file_path) == os.path.abspath(dest_path):
        print("⚠️ File nguồn và đích giống nhau, bỏ qua.")
        return

    os.makedirs(os.path.dirname(dest_path), exist_ok=True)  # Tạo folder nếu chưa có
    shutil.copy2(file_path, dest_path)
    
    remove_line(file_path, "//sync now")  # Xóa ngay lệnh
    print(f"📁 Đã sync: {file_path} -> {dest_path}")
    threading.Thread(target=add_temporary_message, args=(file_path, "📝 ✅ Đã sync!")).start()

def commit_changes(file_path):
    """Tự động commit và push"""
    try:
        repo = git.Repo(WATCH_DIR)
        repo.git.add(A=True)
        repo.index.commit("Auto commit")
        repo.git.push()
        remove_line(file_path, "//commit now")  # Xóa ngay lệnh
        print("✅ Đã commit!")
        threading.Thread(target=add_temporary_message, args=(file_path, "📝 ✅ Đã commit!")).start()
    except Exception as e:
        print(f"⚠️ Lỗi commit: {e}")

class FileEventHandler(FileSystemEventHandler):
    """Xử lý sự kiện khi file thay đổi"""
    def on_modified(self, event):
        if event.is_directory:
            return
        file_path = event.src_path
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                content = f.read()
            if "//sync now" in content:
                sync_file(file_path)
            if "//commit now" in content:
                commit_changes(file_path)
        except Exception as e:
            print(f"⚠️ Lỗi xử lý file {file_path}: {e}")

if __name__ == "__main__":
    print("🚀 Auto-save running... (Ctrl+C để dừng)")
    event_handler = FileEventHandler()
    observer = Observer()
    observer.schedule(event_handler, WATCH_DIR, recursive=True)
    observer.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()
