import os
import time
import shutil
import git
import threading
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
import traceback

WATCH_DIR = os.getcwd()  # Theo dõi thư mục hiện tại
# Thêm các điều kiện hợp lệ để tránh sự kiện lặp
COOLDOWN_PERIOD = 1  # Thời gian chờ giữa các sự kiện (giây)
last_modified_time = {}  # Dictionary để theo dõi thời gian sửa đổi cuối cùng

def read_first_comment(file_path):
    """Đọc dòng đầu tiên để lấy đường dẫn đích"""
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            first_line = f.readline().strip()
            # Hỗ trợ cả comment Python và các ngôn ngữ khác
            if first_line.startswith("//"):
                return first_line[2:].strip()  # Bỏ "//" ở đầu
            elif first_line.startswith("#"):
                return first_line[1:].strip()  # Bỏ "#" ở đầu
    except UnicodeDecodeError:
        # Thử với encoding khác nếu utf-8 thất bại
        try:
            with open(file_path, "r", encoding="latin-1") as f:
                first_line = f.readline().strip()
                if first_line.startswith("//"):
                    return first_line[2:].trip()
                elif first_line.startswith("#"):
                    return first_line[1:].strip()
        except Exception as e:
            print(f"⚠️ Lỗi đọc file {file_path} với encoding khác: {e}")
    except Exception as e:
        print(f"⚠️ Lỗi đọc file {file_path}: {e}")
    return None

def remove_line(file_path, line_to_remove):
    """Xóa một dòng cụ thể trong file"""
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
        with open(file_path, "w", encoding="utf-8") as f:
            # Cải thiện so khớp bằng cách loại bỏ khoảng trắng
            new_lines = [line for line in lines if line.strip() != line_to_remove.strip()]
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
        traceback.print_exc()  # In chi tiết lỗi

def sync_file(file_path):
    """Đồng bộ file đến vị trí đích"""
    dest_path = read_first_comment(file_path)
    if not dest_path:
        print(f"⚠️ Không tìm thấy đường dẫn đích trong {file_path}")
        return
    
    # Kiểm tra xem đường dẫn đích có phải đường dẫn tuyệt đối không
    if os.path.isabs(dest_path):
        # Nếu là đường dẫn tuyệt đối, sử dụng nguyên đường dẫn
        final_dest_path = dest_path
    else:
        # Nếu là đường dẫn tương đối, thêm WATCH_DIR vào trước
        final_dest_path = os.path.join(WATCH_DIR, dest_path)

    # Tránh copy vào chính nó
    if os.path.abspath(file_path) == os.path.abspath(final_dest_path):
        print(f"⚠️ File nguồn và đích giống nhau, bỏ qua: {file_path}")
        return

    try:
        os.makedirs(os.path.dirname(final_dest_path), exist_ok=True)  # Tạo folder nếu chưa có
        shutil.copy2(file_path, final_dest_path)
        
        remove_line(file_path, "//sync now")  # Xóa lệnh cho comment //
        remove_line(file_path, "#sync now")   # Xóa lệnh cho comment #
        print(f"📁 Đã sync: {file_path} -> {final_dest_path}")
        threading.Thread(target=add_temporary_message, args=(file_path, "📝 ✅ Đã sync!")).start()
    except Exception as e:
        print(f"⚠️ Lỗi khi sync file {file_path}: {e}")
        traceback.print_exc()

def commit_changes(file_path):
    """Tự động commit và push"""
    try:
        repo = git.Repo(WATCH_DIR)
        repo.git.add(A=True)
        repo.index.commit("Auto commit")
        origin = repo.remote(name='origin')
        origin.push()
        
        remove_line(file_path, "//commit now")  # Xóa lệnh cho comment //
        remove_line(file_path, "#commit now")   # Xóa lệnh cho comment #
        print("✅ Đã commit và push!")
        threading.Thread(target=add_temporary_message, args=(file_path, "📝 ✅ Đã commit và push!")).start()
    except Exception as e:
        print(f"⚠️ Lỗi commit: {e}")
        traceback.print_exc()

class FileEventHandler(FileSystemEventHandler):
    """Xử lý sự kiện khi file thay đổi"""
    def on_modified(self, event):
        if event.is_directory:
            return
            
        file_path = event.src_path
        current_time = time.time()
        
        # Bỏ qua các file tạm thời hoặc ẩn
        if file_path.endswith(".swp") or file_path.endswith("~") or os.path.basename(file_path).startswith("."):
            return
            
        # Kiểm tra thời gian cooldown để tránh xử lý nhiều lần
        if file_path in last_modified_time:
            if current_time - last_modified_time[file_path] < COOLDOWN_PERIOD:
                return  # Bỏ qua nếu file vừa được xử lý
        
        last_modified_time[file_path] = current_time
        
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                content = f.read()
                
            # Kiểm tra cả hai loại comment
            if "//sync now" in content or "#sync now" in content:
                sync_file(file_path)
                
            if "//commit now" in content or "#commit now" in content:
                commit_changes(file_path)
                
        except UnicodeDecodeError:
            # Thử với encoding khác
            try:
                with open(file_path, "r", encoding="latin-1") as f:
                    content = f.read()
                    
                if "//sync now" in content or "#sync now" in content:
                    sync_file(file_path)
                    
                if "//commit now" in content or "#commit now" in content:
                    commit_changes(file_path)
                    
            except Exception as e:
                print(f"⚠️ Lỗi xử lý file {file_path} với encoding khác: {e}")
        except Exception as e:
            print(f"⚠️ Lỗi xử lý file {file_path}: {e}")

if __name__ == "__main__":
    print("🚀 Auto-save running... (Ctrl+C để dừng)")
    print(f"📂 Đang theo dõi thư mục: {WATCH_DIR}")
    
    event_handler = FileEventHandler()
    observer = Observer()
    observer.schedule(event_handler, WATCH_DIR, recursive=True)
    observer.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
        print("\n🛑 Đã dừng chương trình")
    observer.join()
