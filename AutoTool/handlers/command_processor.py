"""
Command processor module for AutoTool
Detects and processes commands in files
"""
import re
from typing import Optional, Dict, Any, Callable

from ..utils.file_handler import FileHandler
from ..handlers.sync_handler import SyncHandler
from ..handlers.git_handler import GitHandler

class CommandProcessor:
    """Processes commands found in files"""
    
    def __init__(self):
        """Initialize command processor with handlers"""
        self.sync_handler = SyncHandler()
        self.git_handler = GitHandler()
        
    def process_command(self, file_path: str, content: str) -> bool:
        """Process commands in file content
        
        Returns:
            bool: True if any command was processed, False otherwise
        """
        try:
            # Check and process sync command
            if "//sync" in content or "#sync" in content:
                self.sync_handler.sync_file(file_path)
                return True
                
            # Look for advanced commit command with optional branch
            commit_match = re.search(r"(?://|#)commit\s*([a-zA-Z0-9_\-\/]*)?\.", content)
            if commit_match:
                branch = commit_match.group(1).strip() if commit_match.group(1) else None
                self.git_handler.commit_changes(file_path, branch)
                # Remove commit command
                if branch:
                    pattern = f"//commit {branch}." if "//commit" in content else f"#commit {branch}."
                    FileHandler.remove_line(file_path, pattern)
                else:
                    FileHandler.remove_line(file_path, "//commit.")
                    FileHandler.remove_line(file_path, "#commit.")
                return True
                
            # Check for old commit command format (for compatibility)
            if "//commit now" in content or "#commit now" in content:
                self.git_handler.commit_changes(file_path)
                FileHandler.remove_line(file_path, "//commit now")
                FileHandler.remove_line(file_path, "#commit now")
                return True
                
            # Check for status command
            if "//status" in content or "#status" in content:
                self.sync_handler.show_status(file_path)
                return True
            # Check for simple run command
            if "//run" in content or "#run" in content:
                # Only process if it's not part of the more complex "run ... now" pattern
                if "//run " not in content and "#run " not in content:
                    success = self.sync_handler.run_code(file_path)
                    return success   
            # Look for cp command with file name parameter
            cp_match = re.search(r"(?://|#)cp\s+([a-zA-Z0-9_\-]+)", content)
            if cp_match:
                filename = cp_match.group(1).strip()
                self.sync_handler.create_cp_template(file_path, filename)
                return True
                
            # Check for cp command without parameter
            if "//cp" in content or "#cp" in content:
                self.sync_handler.create_cp_template(file_path)
                return True
                
            return False
        except Exception as e:
            from ..utils.status_handler import StatusHandler
            from ..utils.logger import Logger
            
            status_handler = StatusHandler()
            logger = Logger()
            
            error_msg = f"Error processing command: {str(e)}"
            status_handler.add_status_message(file_path, error_msg, "error")
            print(f"⚠️ {error_msg}")
            
            # Log error
            logger.log_operation(file_path, "command_processing", "error", error_msg)
            return False