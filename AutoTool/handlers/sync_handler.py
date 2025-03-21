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
# Compare modification times
import datetime
import subprocess
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
    
    def run_code(self, file_path: str) -> bool:
        """Run code file and display output"""
        try:
            # Find the line where the run command was issued
            run_line = self.status_handler.find_command_line(file_path, "//run")
            if run_line == -1:
                run_line = self.status_handler.find_command_line(file_path, "#run")
            
            if run_line == -1:
                self.logger.log_operation(file_path, "run_code", "error", "No run command found")
                return False
                
            # Get file extension to determine language
            _, ext = os.path.splitext(file_path)
            
            # Define output directory
            output_dir = os.path.join(os.path.dirname(file_path), "output")
            os.makedirs(output_dir, exist_ok=True)
            
            # Base filename without extension
            base_name = os.path.basename(file_path).split('.')[0]
            output_file = os.path.join(output_dir, base_name)
            
            # Execute based on file type
            result = None
            
            if ext.lower() == '.cpp':
                # Compile and run C++ code
                compile_cmd = [
                    '/usr/local/bin/g++-14', '-std=c++17', '-Wall', '-O2',
                    file_path, '-o', output_file
                ]
                
                # Run compilation
                compile_result = subprocess.run(compile_cmd, capture_output=True, text=True)
                
                if compile_result.returncode != 0:
                    # Compilation error
                    error_msg = f"⚠️ Compilation error:\n{compile_result.stderr}"
                    self.status_handler.add_inline_status_message(file_path, run_line, error_msg, "error")
                    self.logger.log_operation(file_path, "run_code", "error", "Compilation failed")
                    return False
                    
                # Run the compiled program
                run_result = subprocess.run([output_file], capture_output=True, text=True, timeout=5)
                result = run_result
            else:
                # Add support for other languages as needed
                message = f"⚠️ Unsupported file type: {ext}"
                self.status_handler.add_inline_status_message(file_path, run_line, message, "error")
                self.logger.log_operation(file_path, "run_code", "error", f"Unsupported file type: {ext}")
                return False
                
            # Create output message
            output_msg = f"✅ Code executed successfully:\n\nSTDOUT:\n{result.stdout}\n"
            if result.stderr:
                output_msg += f"\nSTDERR:\n{result.stderr}\n"
                
            # Add exit code information
            output_msg += f"\nExit code: {result.returncode}"
            
            # Add success message with output
            self.status_handler.add_inline_status_message(file_path, run_line, output_msg, 
                                                         "success" if result.returncode == 0 else "error")
            
            # Remove run command
            FileHandler.remove_line(file_path, "//run")
            FileHandler.remove_line(file_path, "#run")
            
            # Log operation
            self.logger.log_operation(file_path, "run_code", 
                                     "success" if result.returncode == 0 else "error", 
                                     f"Code executed with exit code {result.returncode}")
            return True
        except subprocess.TimeoutExpired:
            error_msg = "⚠️ Execution timed out (5s limit)"
            self.status_handler.add_inline_status_message(file_path, run_line, error_msg, "error")
            self.logger.log_operation(file_path, "run_code", "error", "Execution timed out")
            return False
        except Exception as e:
            error_msg = f"⚠️ Error running code: {str(e)}"
            self.status_handler.add_inline_status_message(file_path, run_line, error_msg, "error")
            traceback.print_exc()
            self.logger.log_operation(file_path, "run_code", "error", error_msg)
            return False