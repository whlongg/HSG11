import os
import time
import shutil
import git
import threading
import datetime
import json
import re
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
import traceback

# Xác định thư mục gốc của dự án thay vì sử dụng thư mục hiện tại
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
WATCH_DIR = SCRIPT_DIR  # Theo dõi thư mục chứa script này
# Thêm các điều kiện hợp lệ để tránh sự kiện lặp
COOLDOWN_PERIOD = 1  # Thời gian chờ giữa các sự kiện (giây)
last_modified_time = {}  # Dictionary để theo dõi thời gian sửa đổi cuối cùng
STATUS_MESSAGE_DURATION = 5  # Thời gian hiển thị thông báo (giây)

# Tạo file log cho user theo dõi lịch sử
LOG_FILE = os.path.join(WATCH_DIR, "autosync_log.json")

# Khởi tạo log nếu chưa tồn tại
if not os.path.exists(LOG_FILE):
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        json.dump([], f)

def log_operation(file_path, operation_type, status, message):
    """Ghi log hoạt động vào file json"""
    try:
        # Đọc log hiện tại
        with open(LOG_FILE, "r", encoding="utf-8") as f:
            try:
                logs = json.load(f)
            except json.JSONDecodeError:
                logs = []
        
        # Thêm bản ghi mới
        logs.append({
            "timestamp": datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            "file": file_path,
            "operation": operation_type,
            "status": status,
            "message": message
        })
        
        # Giới hạn số lượng log (giữ 100 bản ghi gần nhất)
        if len(logs) > 100:
            logs = logs[-100:]
            
        # Lưu log
        with open(LOG_FILE, "w", encoding="utf-8") as f:
            json.dump(logs, f, indent=2)
    except Exception as e:
        print(f"⚠️ Lỗi khi ghi log: {e}")

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
                    return first_line[2:].strip()  # Sửa lỗi từ trip() sang strip()
                elif first_line.startswith("#"):
                    return first_line[1:].strip()
        except Exception as e:
            add_status_message(file_path, f"⚠️ Lỗi đọc file với encoding khác: {e}", "error")
            print(f"⚠️ Lỗi đọc file {file_path} với encoding khác: {e}")
    except Exception as e:
        add_status_message(file_path, f"⚠️ Lỗi đọc file: {e}", "error")
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

def remove_section_markers(file_path):
    """Xóa các dấu hiệu phần trạng thái trong file"""
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
            
        # Tìm và xóa phần STATUS SECTION
        start_idx = -1
        end_idx = -1
        
        for i, line in enumerate(lines):
            if line.strip() == "/* AUTO-SYNC STATUS START */":
                start_idx = i
            elif line.strip() == "/* AUTO-SYNC STATUS END */":
                end_idx = i
                
        # Nếu tìm thấy cả điểm bắt đầu và kết thúc, xóa phần này
        if start_idx != -1 and end_idx != -1 and start_idx < end_idx:
            new_lines = lines[:start_idx] + lines[end_idx+1:]
            with open(file_path, "w", encoding="utf-8") as f:
                f.writelines(new_lines)
    except Exception as e:
        print(f"⚠️ Lỗi khi xóa section markers: {e}")

def clean_file(file_path):
    """Xóa lệnh và thông báo trạng thái khỏi file"""
    try:
        # Xóa phần trạng thái
        remove_section_markers(file_path)
        
        # Xóa tất cả các loại lệnh
        with open(file_path, "r", encoding="utf-8") as f:
            lines = f.readlines()
        
        # Danh sách các lệnh cần xóa
        commands = ["//sync", "#sync", 
                    "//commit now", "#commit now", 
                    "//status", "#status"]
        
        # Thêm các mẫu lệnh commit mới vào danh sách cần xóa
        commit_patterns = [
            r"//commit\.", r"#commit\.",
            r"//commit\s+[a-zA-Z0-9_\-\/]+\.", r"#commit\s+[a-zA-Z0-9_\-\/]+\."
        ]
        
        # Lọc các dòng không chứa lệnh
        new_lines = []
        for line in lines:
            should_keep = True
            # Kiểm tra các lệnh cụ thể
            for cmd in commands:
                if cmd in line:
                    should_keep = False
                    break
            
            # Kiểm tra các mẫu lệnh commit mới
            if should_keep:
                for pattern in commit_patterns:
                    if re.search(pattern, line):
                        should_keep = False
                        break
            
            if should_keep:
                new_lines.append(line)
        
        # Ghi lại nội dung file sau khi xóa lệnh
        with open(file_path, "w", encoding="utf-8") as f:
            f.writelines(new_lines)
            
    except Exception as e:
        print(f"⚠️ Lỗi khi làm sạch file {file_path}: {e}")

def add_status_message(file_path, message, status_type="info"):
    """Thêm thông báo trạng thái vào file"""
    try:
        # Xóa section marker cũ nếu có
        remove_section_markers(file_path)
        
        with open(file_path, "r", encoding="utf-8") as f:
            content = f.readlines()
            
        # Thêm thông báo vào cuối file với định dạng đẹp hơn
        timestamp = datetime.datetime.now().strftime("%H:%M:%S %d/%m/%Y")
        
        # Chọn icon phù hợp với loại trạng thái
        icon = "ℹ️" if status_type == "info" else "✅" if status_type == "success" else "⚠️"
        
        status_section = [
            "\n/* AUTO-SYNC STATUS START */\n",
            f"/* {icon} {message} */\n",
            f"/* ⏱️ Thời gian: {timestamp} */\n",
            "/* AUTO-SYNC STATUS END */\n"
        ]
        
        with open(file_path, "w", encoding="utf-8") as f:
            f.writelines(content + status_section)
            
        # Log hoạt động
        log_operation(file_path, "status_update", status_type, message)
    except Exception as e:
        print(f"⚠️ Lỗi khi thêm thông báo trạng thái: {e}")
        traceback.print_exc()

def get_commit_message():
    """Tạo commit message với timestamp"""
    return f"Auto commit at {datetime.datetime.now().strftime('%H:%M:%S %d/%m/%Y')}"

def sync_file(file_path):
    """Đồng bộ file đến vị trí đích"""
    dest_path = read_first_comment(file_path)
    if not dest_path:
        message = "⚠️ Không tìm thấy đường dẫn đích trong file"
        add_status_message(file_path, message, "error")
        print(f"{message}: {file_path}")
        return False
    
    # Kiểm tra xem đường dẫn đích có phải đường dẫn tuyệt đối không
    if os.path.isabs(dest_path):
        # Nếu là đường dẫn tuyệt đối, sử dụng nguyên đường dẫn
        final_dest_path = dest_path
    else:
        # Nếu là đường dẫn tương đối, thêm WATCH_DIR vào trước
        final_dest_path = os.path.join(WATCH_DIR, dest_path)

    # Tránh copy vào chính nó
    if os.path.abspath(file_path) == os.path.abspath(final_dest_path):
        message = "⚠️ File nguồn và đích giống nhau, bỏ qua"
        add_status_message(file_path, message, "error")
        print(f"{message}: {file_path}")
        return False

    try:
        # Đảm bảo thư mục đích tồn tại
        os.makedirs(os.path.dirname(final_dest_path), exist_ok=True)
        
        # Tạo bản sao tạm thời của file gốc sau khi làm sạch
        temp_file = file_path + ".temp"
        shutil.copy2(file_path, temp_file)
        clean_file(temp_file)
        
        # Copy file đã làm sạch đến đích
        shutil.copy2(temp_file, final_dest_path)
        
        # Xóa file tạm
        if os.path.exists(temp_file):
            os.remove(temp_file)
        
        # Xóa lệnh khỏi file gốc
        remove_line(file_path, "//sync")
        remove_line(file_path, "#sync")
        
        # Thêm thông báo vào file gốc
        message = f"✅ Đã đồng bộ đến {final_dest_path}"
        add_status_message(file_path, message, "success")
        print(f"📁 {message}")
        
        # Log hoạt động thành công
        log_operation(file_path, "sync", "success", f"Đã đồng bộ đến {final_dest_path}")
        return True
    except Exception as e:
        error_msg = f"Lỗi khi đồng bộ: {str(e)}"
        add_status_message(file_path, error_msg, "error")
        print(f"⚠️ {error_msg}")
        traceback.print_exc()
        
        # Log lỗi
        log_operation(file_path, "sync", "error", error_msg)
        return False

def commit_changes(file_path, branch=None):
    """Tự động commit và push"""
    try:
        # Thêm thông báo đang xử lý
        if branch:
            add_status_message(file_path, f"Đang commit lên nhánh '{branch}'...", "info")
        else:
            add_status_message(file_path, "Đang thực hiện commit...", "info")
        
        repo = git.Repo(WATCH_DIR)
        
        # Kiểm tra trạng thái git
        if not repo.is_dirty() and len(repo.untracked_files) == 0:
            message = "Không có thay đổi để commit"
            add_status_message(file_path, message, "info")
            print(f"ℹ️ {message}")
            return
        
        # Lưu branch hiện tại để có thể chuyển trở lại sau này
        current_branch = repo.active_branch.name
        
        # Chuyển sang branch mới nếu được chỉ định
        if branch and branch != current_branch:
            try:
                # Kiểm tra xem nhánh đã tồn tại hay chưa
                branch_exists = branch in [b.name for b in repo.branches]
                
                if not branch_exists:
                    # Tạo nhánh mới nếu chưa tồn tại
                    repo.git.branch(branch)
                    message = f"✅ Đã tạo nhánh mới '{branch}'"
                    print(message)
                
                # Chuyển sang nhánh mới
                repo.git.checkout(branch)
                message = f"✅ Đã chuyển sang nhánh '{branch}'"
                print(message)
                
            except Exception as e:
                error_msg = f"Lỗi khi chuyển nhánh sang '{branch}': {str(e)}"
                add_status_message(file_path, error_msg, "error")
                print(f"⚠️ {error_msg}")
                return
        
        # Thực hiện add và commit
        repo.git.add(A=True)  # Thêm tất cả file
        commit_msg = get_commit_message()
        commit = repo.index.commit(commit_msg)
        
        # Lấy thông tin branch hiện tại
        branch_name = repo.active_branch.name
        
        # Push lên remote
        try:
            origin = repo.remote(name='origin')
            push_info = origin.push(refspec=f"{branch_name}:{branch_name}")
            
            # Kiểm tra kết quả push
            if hasattr(push_info[0], 'flags') and push_info[0].flags & push_info[0].ERROR:
                raise Exception(f"Push thất bại: {push_info[0].summary}")
                
            # Nếu thành công
            message = f"✅ Đã commit và push lên branch '{branch_name}'\n⏱️ {commit_msg}\n📝 SHA: {commit.hexsha[:7]}"
            add_status_message(file_path, message, "success")
            print(f"✅ {message}")
            
            # Log hoạt động thành công
            log_operation(file_path, "commit", "success", 
                          f"Commit '{commit_msg}' lên branch '{branch_name}', SHA: {commit.hexsha[:7]}")
            
        except Exception as e:
            # Nếu push thất bại nhưng commit thành công
            error_msg = f"Commit thành công nhưng push thất bại: {str(e)}"
            add_status_message(file_path, error_msg, "error")
            print(f"⚠️ {error_msg}")
            
            # Log lỗi
            log_operation(file_path, "push", "error", error_msg)
            
        # Trở lại nhánh ban đầu nếu đã thay đổi
        if branch and branch != current_branch:
            try:
                repo.git.checkout(current_branch)
                print(f"✅ Đã trở lại nhánh '{current_branch}'")
            except Exception as e:
                print(f"⚠️ Lỗi khi trở lại nhánh '{current_branch}': {str(e)}")
        
    except Exception as e:
        error_msg = f"Lỗi khi commit: {str(e)}"
        add_status_message(file_path, error_msg, "error")
        print(f"⚠️ {error_msg}")
        traceback.print_exc()
        
        # Log lỗi
        log_operation(file_path, "commit", "error", error_msg)

def show_status(file_path):
    """Hiển thị trạng thái đồng bộ của file"""
    try:
        dest_path = read_first_comment(file_path)
        if not dest_path:
            message = "⚠️ Không tìm thấy đường dẫn đích trong file"
            add_status_message(file_path, message, "error")
            return
            
        # Xác định đường dẫn đích đầy đủ
        if os.path.isabs(dest_path):
            final_dest_path = dest_path
        else:
            final_dest_path = os.path.join(WATCH_DIR, dest_path)
            
        # Kiểm tra xem file đích có tồn tại không
        if not os.path.exists(final_dest_path):
            message = f"⚠️ File đích không tồn tại: {final_dest_path}"
            add_status_message(file_path, message, "error")
            return
            
        # So sánh thời gian sửa đổi
        src_mtime = os.path.getmtime(file_path)
        dest_mtime = os.path.getmtime(final_dest_path)
        
        src_time = datetime.datetime.fromtimestamp(src_mtime).strftime('%H:%M:%S %d/%m/%Y')
        dest_time = datetime.datetime.fromtimestamp(dest_mtime).strftime('%H:%M:%S %d/%m/%Y')
        
        if src_mtime > dest_mtime:
            message = f"⚠️ File nguồn mới hơn file đích\n📝 Nguồn: {src_time}\n📝 Đích: {dest_time}"
            add_status_message(file_path, message, "info")
        elif src_mtime < dest_mtime:
            message = f"⚠️ File đích mới hơn file nguồn\n📝 Nguồn: {src_time}\n📝 Đích: {dest_time}"
            add_status_message(file_path, message, "info")
        else:
            message = f"✅ File nguồn và đích đồng bộ\n📝 Cập nhật lần cuối: {src_time}"
            add_status_message(file_path, message, "success")
            
        # Log hoạt động
        log_operation(file_path, "status_check", "info", message)
        
        # Xóa lệnh
        remove_line(file_path, "//status")
        remove_line(file_path, "#status")
        
    except Exception as e:
        error_msg = f"Lỗi khi kiểm tra trạng thái: {str(e)}"
        add_status_message(file_path, error_msg, "error")
        print(f"⚠️ {error_msg}")
        traceback.print_exc()
        
        # Log lỗi
        log_operation(file_path, "status_check", "error", error_msg)
        
        # Xóa lệnh
        remove_line(file_path, "//status")
        remove_line(file_path, "#status")

def process_command(file_path, content):
    """Xử lý các lệnh trong file"""
    try:
        # Tìm kiếm và xử lý các lệnh đồng bộ
        if "//sync" in content or "#sync" in content:
            sync_file(file_path)
            return True
            
        # Tìm kiếm lệnh commit nâng cao
        commit_match = re.search(r"(?://|#)commit\s*([a-zA-Z0-9_\-\/]*)?\.", content)
        if commit_match:
            branch = commit_match.group(1).strip() if commit_match.group(1) else None
            commit_changes(file_path, branch)
            # Xóa lệnh commit
            if branch:
                pattern = f"//commit {branch}." if "//commit" in content else f"#commit {branch}."
                remove_line(file_path, pattern)
            else:
                remove_line(file_path, "//commit.")
                remove_line(file_path, "#commit.")
            return True
            
        # Tìm kiếm lệnh commit cũ (giữ lại để tương thích)
        if "//commit now" in content or "#commit now" in content:
            commit_changes(file_path)
            remove_line(file_path, "//commit now")
            remove_line(file_path, "#commit now")
            return True
            
        # Tìm kiếm lệnh status
        if "//status" in content or "#status" in content:
            show_status(file_path)
            return True
            
        return False
    except Exception as e:
        error_msg = f"Lỗi khi xử lý lệnh: {str(e)}"
        add_status_message(file_path, error_msg, "error")
        print(f"⚠️ {error_msg}")
        traceback.print_exc()
        return False

class FileEventHandler(FileSystemEventHandler):
    """Xử lý sự kiện khi file thay đổi"""
    def on_modified(self, event):
        if event.is_directory:
            return
            
        file_path = event.src_path
        current_time = time.time()
        
        # Bỏ qua các file tạm thời, ẩn, hoặc file log của chính chúng ta
        if (file_path.endswith(".swp") or file_path.endswith("~") or 
            file_path.endswith(".temp") or os.path.basename(file_path).startswith(".") or 
            file_path == LOG_FILE):
            return
            
        # Kiểm tra thời gian cooldown để tránh xử lý nhiều lần
        if file_path in last_modified_time:
            if current_time - last_modified_time[file_path] < COOLDOWN_PERIOD:
                return  # Bỏ qua nếu file vừa được xử lý
        
        last_modified_time[file_path] = current_time
        
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                content = f.read()
                
            # Xử lý tất cả các lệnh
            process_command(file_path, content)
                
        except UnicodeDecodeError:
            # Thử với encoding khác
            try:
                with open(file_path, "r", encoding="latin-1") as f:
                    content = f.read()
                    
                # Xử lý tất cả các lệnh với encoding khác
                process_command(file_path, content)
                    
            except Exception as e:
                #print(f"⚠️ Lỗi xử lý file {file_path} với encoding khác: {e}")
                pass
        except Exception as e:
            # print(f"⚠️ Lỗi xử lý file {file_path}: {e}")
            pass

if __name__ == "__main__":
    print("🚀 Auto-sync running... (Ctrl+C để dừng)")
    print(f"📂 Đang theo dõi thư mục: {WATCH_DIR}")
    print(f"📝 Log file: {LOG_FILE}")
    print("📋 Lệnh hỗ trợ:")
    print("   - //sync: Đồng bộ file đến đích")
    print("   - //commit.: Commit lên nhánh hiện tại")
    print("   - //commit tên_nhánh.: Commit lên nhánh chỉ định")
    print("   - //status: Kiểm tra trạng thái đồng bộ")
    
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














/* AUTO-SYNC STATUS START */
/* ℹ️ Đang thực hiện commit... */
/* ⏱️ Thời gian: 02:45:57 18/03/2025 */
/* AUTO-SYNC STATUS END */
