"""
Sync handler module for AutoTool
Handles file synchronization operations
"""
import os
import shutil
import traceback
import filecmp
import re
from typing import Optional, Tuple, Dict, List

from ..utils.file_handler import FileHandler
from ..utils.status_handler import StatusHandler
from ..utils.logger import Logger
from ..utils.config import Config

class SyncHandler:
    """Handles file synchronization operations"""
    
    def __init__(self):
        """Initialize sync handler"""
        self.config = Config()
        self.status_handler = StatusHandler()
        self.logger = Logger()
    
    def sync_file(self, file_path: str) -> bool:
        """Synchronize a file to its target location"""
        # Find the line where the sync command was issued
        sync_line = self.status_handler.find_command_line(file_path, "//sync")
        if sync_line == -1:
            sync_line = self.status_handler.find_command_line(file_path, "#sync")
        
        dest_path = FileHandler.read_first_comment(file_path)
        if not dest_path:
            message = "⚠️ No target path found in file"
            self.status_handler.add_inline_status_message(file_path, sync_line, message, "error")
            self.logger.log_operation(file_path, "sync", "error", "No target path found")
            return False
        
        # Check if the target path is absolute or relative
        if os.path.isabs(dest_path):
            # If absolute, use path as is
            final_dest_path = dest_path
        else:
            # If relative, prepend watch directory
            final_dest_path = os.path.join(self.config.WATCH_DIR, dest_path)

        # Avoid copying to itself
        if os.path.abspath(file_path) == os.path.abspath(final_dest_path):
            message = "⚠️ Source and destination are the same, skipping"
            self.status_handler.add_inline_status_message(file_path, sync_line, message, "error")
            
            # Remove sync command to avoid infinite loop
            FileHandler.remove_line(file_path, "//sync")
            FileHandler.remove_line(file_path, "#sync")
            
            self.logger.log_operation(file_path, "sync", "error", "Source and destination are the same")
            return False

        try:
            # Create temporary clean copy of the file
            temp_file = file_path + ".temp"
            shutil.copy2(file_path, temp_file)
            FileHandler.clean_file(temp_file)
            
            # Create destination directory if needed
            os.makedirs(os.path.dirname(final_dest_path), exist_ok=True)
            
            # Check if content is identical (ignoring commands/status messages)
            is_content_identical = False
            if os.path.exists(final_dest_path):
                # Create temporary clean copy of destination for comparison
                dest_temp_file = final_dest_path + ".temp"
                shutil.copy2(final_dest_path, dest_temp_file)
                
                # Compare cleaned files
                is_content_identical = filecmp.cmp(temp_file, dest_temp_file, shallow=False)
                
                # Remove temporary destination file
                if os.path.exists(dest_temp_file):
                    os.remove(dest_temp_file)
            
            # If files are identical, don't copy and remove sync command
            if is_content_identical:
                message = "✅ Files are already identical, no sync needed"
                self.status_handler.add_inline_status_message(file_path, sync_line, message, "success")
                
                # Remove sync command to avoid infinite loop
                FileHandler.remove_line(file_path, "//sync")
                FileHandler.remove_line(file_path, "#sync")
                
                # Remove temporary source file
                if os.path.exists(temp_file):
                    os.remove(temp_file)
                
                self.logger.log_operation(file_path, "sync", "success", "Files already identical")
                return True
            
            # Copy cleaned file to destination
            shutil.copy2(temp_file, final_dest_path)
            
            # Remove temporary file
            if os.path.exists(temp_file):
                os.remove(temp_file)
            
            # Remove sync command from source file
            FileHandler.remove_line(file_path, "//sync")
            FileHandler.remove_line(file_path, "#sync")
            
            # Add success message
            message = f"✅ Synchronized to {final_dest_path}"
            self.status_handler.add_inline_status_message(file_path, sync_line, message, "success")
            
            # Log successful operation
            self.logger.log_operation(file_path, "sync", "success", f"Synchronized to {final_dest_path}")
            return True
        except Exception as e:
            error_msg = f"Error during synchronization: {str(e)}"
            self.status_handler.add_inline_status_message(file_path, sync_line, error_msg, "error")
            traceback.print_exc()
            
            # Remove sync command even if error occurred to avoid infinite loop
            FileHandler.remove_line(file_path, "//sync")
            FileHandler.remove_line(file_path, "#sync")
            
            # Log error
            self.logger.log_operation(file_path, "sync", "error", error_msg)
            return False

    def show_status(self, file_path: str) -> None:
        """Show synchronization status of a file"""
        try:
            # Find the line where the status command was issued
            status_line = self.status_handler.find_command_line(file_path, "//status")
            if status_line == -1:
                status_line = self.status_handler.find_command_line(file_path, "#status")
            
            dest_path = FileHandler.read_first_comment(file_path)
            if not dest_path:
                message = "⚠️ No target path found in file"
                self.status_handler.add_inline_status_message(file_path, status_line, message, "error")
                return
                
            # Determine full destination path
            if os.path.isabs(dest_path):
                final_dest_path = dest_path
            else:
                final_dest_path = os.path.join(self.config.WATCH_DIR, dest_path)
                
            # Check if destination file exists
            if not os.path.exists(final_dest_path):
                message = f"⚠️ Destination file doesn't exist: {final_dest_path}"
                self.status_handler.add_inline_status_message(file_path, status_line, message, "error")
                return
                
            # Compare modification times
            import datetime
            src_mtime = os.path.getmtime(file_path)
            dest_mtime = os.path.getmtime(final_dest_path)
            
            src_time = datetime.datetime.fromtimestamp(src_mtime).strftime('%H:%M:%S %d/%m/%Y')
            dest_time = datetime.datetime.fromtimestamp(dest_mtime).strftime('%H:%M:%S %d/%m/%Y')
            
            if src_mtime > dest_mtime:
                message = f"⚠️ Source file is newer than destination\n📝 Source: {src_time}\n📝 Destination: {dest_time}"
                self.status_handler.add_inline_status_message(file_path, status_line, message, "info")
            elif src_mtime < dest_mtime:
                message = f"⚠️ Destination file is newer than source\n📝 Source: {src_time}\n📝 Destination: {dest_time}"
                self.status_handler.add_inline_status_message(file_path, status_line, message, "info")
            else:
                message = f"✅ Source and destination are synchronized\n📝 Last updated: {src_time}"
                self.status_handler.add_inline_status_message(file_path, status_line, message, "success")
                
            # Log operation
            self.logger.log_operation(file_path, "status_check", "info", message)
            
            # Remove status command
            FileHandler.remove_line(file_path, "//status")
            FileHandler.remove_line(file_path, "#status")
            
        except Exception as e:
            error_msg = f"Error checking status: {str(e)}"
            self.status_handler.add_status_message(file_path, error_msg, "error")
            print(f"⚠️ {error_msg}")
            traceback.print_exc()
            
            # Log error
            self.logger.log_operation(file_path, "status_check", "error", error_msg)
            
            # Remove status command even if error occurred
            FileHandler.remove_line(file_path, "//status")
            FileHandler.remove_line(file_path, "#status")
            
    def create_cp_template(self, file_path: str, filename: str = None) -> bool:
        """Copy template content to the current file"""
        try:
            # Find the line where the cp command was issued
            cp_line = -1
            if filename:
                cp_line = self.status_handler.find_command_line(file_path, f"//cp {filename}")
                if cp_line == -1:
                    cp_line = self.status_handler.find_command_line(file_path, f"#cp {filename}")
            else:
                cp_line = self.status_handler.find_command_line(file_path, "//cp")
                if cp_line == -1:
                    cp_line = self.status_handler.find_command_line(file_path, "#cp")
            
            # Check if template file exists
            if not os.path.exists(self.config.TEMPLATE_FILE):
                error_msg = f"⚠️ Template does not exist at {self.config.TEMPLATE_FILE}"
                self.status_handler.add_inline_status_message(file_path, cp_line, error_msg, "error")
                self.logger.log_operation(file_path, "cp_template", "error", error_msg)
                return False
            
            # Read template content
            with open(self.config.TEMPLATE_FILE, 'r', encoding='utf-8') as f:
                template_content = f.read()
            
            # Preserve the first comment line from the current file (destination comment)
            first_line = None
            with open(file_path, 'r', encoding='utf-8') as f:
                first_line = f.readline().strip()
                
            # Write template content to current file but preserve first line if it's a path comment
            with open(file_path, 'w', encoding='utf-8') as f:
                if (first_line and (first_line.startswith('//') or first_line.startswith('#'))):
                    f.write(first_line + '\n')
                f.write(template_content)
            
            # Remove cp command
            FileHandler.remove_line(file_path, "//cp")
            FileHandler.remove_line(file_path, "#cp")
            
            # Remove cp command with parameter if applicable
            if filename:
                FileHandler.remove_line(file_path, f"//cp {filename}")
                FileHandler.remove_line(file_path, f"#cp {filename}")
            
            # Add success message
            message = "✅ Template applied to current file"
            self.status_handler.add_inline_status_message(file_path, cp_line, message, "success")
            
            # Log operation
            self.logger.log_operation(file_path, "cp_template", "success", "Applied template to current file")
            return True
        except Exception as e:
            error_msg = f"⚠️ Error applying template: {str(e)}"
            self.status_handler.add_status_message(file_path, error_msg, "error")
            traceback.print_exc()
            
            # Log error
            self.logger.log_operation(file_path, "cp_template", "error", error_msg)
            return False
    
    def run_code(self, file_path: str, args: str) -> bool:
        """Run the code with given arguments and show output at the command's location
        
        Args:
            file_path (str): Path to the source code file
            args (str): Command line arguments or input data as a string
                
        Returns:
            bool: True if execution was successful, False otherwise
        """
        try:
            import subprocess
            import tempfile
            import datetime
            import os
            import re
            import shutil
            
            # Get file extension to determine language
            _, ext = os.path.splitext(file_path)
            
            if ext.lower() == '.cpp':
                # Create temporary executable
                temp_dir = tempfile.mkdtemp()
                exe_path = os.path.join(temp_dir, "program")
                
                # Compile the code
                compile_cmd = ["g++", "-std=c++17", "-O2", file_path, "-o", exe_path]
                compile_process = subprocess.run(compile_cmd, capture_output=True, text=True)
                
                if compile_process.returncode != 0:
                    # Compilation failed
                    error_msg = f"⚠️ Compilation error:\n{compile_process.stderr}"
                    self.status_handler.add_status_message(file_path, error_msg, "error")
                    print(error_msg)
                    self.logger.log_operation(file_path, "run", "error", "Compilation failed")
                    return False
                
                # Tạo file tạm để chứa input
                input_file = os.path.join(temp_dir, "input.txt")
                with open(input_file, "w", encoding="utf-8") as f:
                    f.write(args)
                
                # Tạo file tạm để chứa output
                output_file = os.path.join(temp_dir, "output.txt")
                
                # Chạy executable với input từ file và output vào file
                try:
                    with open(input_file, "r") as infile, open(output_file, "w") as outfile:
                        process = subprocess.Popen(
                            [exe_path],
                            stdin=infile,
                            stdout=outfile,
                            stderr=subprocess.PIPE,
                            text=True
                        )
                    
                    stderr = process.communicate(timeout=5)[1]
                    return_code = process.returncode
                    
                    # Đọc output từ file
                    with open(output_file, "r", encoding="utf-8") as f:
                        stdout = f.read()
                    
                except subprocess.TimeoutExpired:
                    process.kill()
                    stderr = process.communicate()[1]
                    stdout = "Execution timed out"
                    error_msg = "⚠️ Program execution timed out (limit: 5 seconds)"
                    self.status_handler.add_status_message(file_path, error_msg, "error")
                    print(error_msg)
                    self.logger.log_operation(file_path, "run", "error", "Execution timed out")
                    return False
                
                # Get execution timestamp
                timestamp = datetime.datetime.now().strftime("%H:%M:%S %d/%m/%Y")
                
                # Find the run command line
                run_line_idx = -1
                run_pattern = re.compile(r"//run\s+|#run\s+")
                
                with open(file_path, "r", encoding="utf-8") as f:
                    lines = f.readlines()
                    for i, line in enumerate(lines):
                        if run_pattern.search(line):
                            run_line_idx = i
                            break
                
                if run_line_idx == -1:
                    run_line_idx = len(lines) - 1
                    print(f"⚠️ Could not find run command line in {file_path}")
                    self.logger.log_operation(file_path, "run", "warning", "Could not find run command line")
                
                # Format the output message
                output_lines = [
                    "// -------- RUN RESULT --------\n",
                    f"// ⏱️ Executed at: {timestamp}\n",
                    "// ARG:\n"
                ]
                
                # Thêm input, giữ nguyên định dạng xuống dòng
                input_lines = args.split('\n')
                for line in input_lines:
                    output_lines.append(f"// {line}\n")
                
                output_lines.append("// OUTPUT:\n")
                
                # Kiểm tra output.txt ở thư mục của file nguồn
                source_output_file = os.path.join(os.path.dirname(file_path), "output.txt")
                if os.path.exists(source_output_file):
                    # Đọc nội dung output.txt
                    try:
                        with open(source_output_file, "r", encoding="utf-8") as f:
                            source_output = f.read().strip()
                        
                        # Xóa file output.txt sau khi đọc
                        os.remove(source_output_file)
                        
                        # Thêm output từ file
                        if source_output:
                            output_lines_content = source_output.split('\n')
                            for line in output_lines_content:
                                output_lines.append(f"// {line}\n")
                        else:
                            output_lines.append("// [No Output]\n")
                    except Exception as e:
                        output_lines.append(f"// Error reading output.txt: {str(e)}\n")
                        # Sử dụng stdout từ process
                        if stdout and stdout.strip():
                            output_lines_content = stdout.strip().split('\n')
                            for line in output_lines_content:
                                output_lines.append(f"// {line}\n")
                        else:
                            output_lines.append("// [No Output]\n")
                else:
                    # Sử dụng stdout từ process
                    if stdout and stdout.strip():
                        output_lines_content = stdout.strip().split('\n')
                        for line in output_lines_content:
                            output_lines.append(f"// {line}\n")
                    else:
                        output_lines.append("// [No Output]\n")
                
                # Thêm lỗi nếu có
                if stderr and stderr.strip():
                    output_lines.append("// ERROR:\n")
                    stderr_lines = stderr.strip().split('\n')
                    for line in stderr_lines:
                        output_lines.append(f"// {line}\n")
                
                # Thêm return code
                output_lines.append(f"// Return code: {return_code}\n")
                output_lines.append("// ---------------------------\n")
                
                # Thay thế dòng lệnh run bằng kết quả
                if run_line_idx < len(lines):
                    lines[run_line_idx] = "".join(output_lines)
                else:
                    lines.append("".join(output_lines))
                
                # Ghi lại nội dung đã sửa
                with open(file_path, "w", encoding="utf-8") as f:
                    f.writelines(lines)
                
                print(f"🚀 Executed {file_path}")
                self.logger.log_operation(file_path, "run", "success", "Execution successful")
                
                # Dọn dẹp file tạm
                try:
                    shutil.rmtree(temp_dir)
                except Exception as e:
                    print(f"Warning: Failed to clean up temporary directory: {e}")
                    
                return True
            
            else:
                error_msg = f"⚠️ Unsupported file type: {ext}. Only C++ (.cpp) files are supported for now."
                self.status_handler.add_status_message(file_path, error_msg, "error")
                print(error_msg)
                self.logger.log_operation(file_path, "run", "error", "Unsupported file type")
                return False
                
        except Exception as e:
            error_msg = f"⚠️ Error running code: {str(e)}"
            self.status_handler.add_status_message(file_path, error_msg, "error")
            print(error_msg)
            import traceback
            traceback.print_exc()
            self.logger.log_operation(file_path, "run", "error", error_msg)
            return False