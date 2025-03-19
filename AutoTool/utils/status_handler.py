"""
Status handler module for AutoTool
Manages status messages and notifications
"""
import os
import datetime
import threading
from typing import Dict, Optional, Callable, Union

from .file_handler import FileHandler
from .logger import Logger

class StatusHandler:
    """Handles status messages and notifications"""
    _instance = None
    
    def __new__(cls):
        """Singleton pattern implementation"""
        if cls._instance is None:
            cls._instance = super(StatusHandler, cls).__new__(cls)
            cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        """Initialize status handler"""
        if self._initialized:
            return
            
        from .config import Config
        self.config = Config()
        self.logger = Logger()
        self.pending_status_removals: Dict[str, threading.Timer] = {}
        
        # Define message timeouts based on type (in seconds)
        self.message_timeouts = {
            "success": self.config.STATUS_MESSAGE_DURATION,
            "info": 5.0,  # Info messages display for 5 seconds
            "error": 10.0  # Error messages display for 10 seconds
        }
        
        self._initialized = True
    
    def add_status_message(self, file_path: str, message: str, status_type: str = "info") -> None:
        """Add a status message to a file"""
        try:
            # Remove existing status section if present
            FileHandler.remove_section_markers(file_path)
            
            with open(file_path, "r", encoding="utf-8") as f:
                content = f.readlines()
                
            # Add message at the end of the file with prettier formatting
            timestamp = datetime.datetime.now().strftime("%H:%M:%S %d/%m/%Y")
            
            # Select appropriate icon based on status type
            icon = "ℹ️" if status_type == "info" else "✅" if status_type == "success" else "⚠️"
            
            status_section = [
                "\n/* AUTO-SYNC STATUS START */\n",
                f"/* {icon} {message} */\n",
                f"/* ⏱️ Thời gian: {timestamp} */\n",
                "/* AUTO-SYNC STATUS END */\n"
            ]
            
            with open(file_path, "w", encoding="utf-8") as f:
                f.writelines(content + status_section)
                
            # Log the operation
            self.logger.log_operation(file_path, "status_update", status_type, message)
            
            # Schedule automatic removal for all message types with appropriate timeouts
            delay = self.message_timeouts.get(status_type, 5.0)  # Default to 5 seconds if type not recognized
            self.schedule_status_removal(file_path, delay)
            
        except Exception as e:
            print(f"⚠️ Error adding status message: {e}")
    
    def add_inline_status_message(self, file_path: str, line_index: int, message: str, status_type: str = "info") -> None:
        """Add a status message at a specific line in the file"""
        try:
            # Remove existing status section first
            FileHandler.remove_section_markers(file_path)
            
            with open(file_path, "r", encoding="utf-8") as f:
                lines = f.readlines()
            
            # Ensure line_index is within bounds
            if line_index < 0:
                line_index = 0
            elif line_index >= len(lines):
                line_index = len(lines) - 1
            
            timestamp = datetime.datetime.now().strftime("%H:%M:%S %d/%m/%Y")
            
            # Select appropriate icon based on status type
            icon = "ℹ️" if status_type == "info" else "✅" if status_type == "success" else "⚠️"
            
            # Create the status message
            status_lines = [
                "/* AUTO-SYNC STATUS START */\n",
                f"/* {icon} {message} */\n",
                f"/* ⏱️ Thời gian: {timestamp} */\n",
                "/* AUTO-SYNC STATUS END */\n"
            ]
            
            # Insert the status lines at the specified position
            lines.insert(line_index + 1, "".join(status_lines))
            
            with open(file_path, "w", encoding="utf-8") as f:
                f.writelines(lines)
            
            # Log the operation
            self.logger.log_operation(file_path, "inline_status_update", status_type, message)
            
            # Schedule automatic removal
            delay = self.message_timeouts.get(status_type, 5.0)
            self.schedule_status_removal(file_path, delay)
            
        except Exception as e:
            print(f"⚠️ Error adding inline status message: {e}")
    
    def find_command_line(self, file_path: str, command: str) -> int:
        """Find the line number containing a specific command"""
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                lines = f.readlines()
            
            for i, line in enumerate(lines):
                if command in line:
                    return i
                    
            return -1  # Command not found
        except Exception:
            return -1
    
    def schedule_status_removal(self, file_path: str, delay: float) -> None:
        """Schedule removal of status message after a delay"""
        def remove_status():
            try:
                if file_path in self.pending_status_removals:
                    del self.pending_status_removals[file_path]
                    FileHandler.remove_section_markers(file_path)
            except Exception as e:
                print(f"⚠️ Error removing status message: {e}")

        # Cancel existing timer if present
        if file_path in self.pending_status_removals:
            self.pending_status_removals[file_path].cancel()
        
        # Create new timer
        timer = threading.Timer(delay, remove_status)
        timer.daemon = True
        self.pending_status_removals[file_path] = timer
        timer.start()