"""
Logger module for AutoTool
Handles logging operations to JSON file
"""
import os
import json
import datetime
from typing import List, Dict, Any

class Logger:
    """Logger for AutoTool operations"""
    _instance = None
    
    def __new__(cls, log_file: str = None):
        """Singleton pattern implementation"""
        if cls._instance is None:
            cls._instance = super(Logger, cls).__new__(cls)
            cls._instance._initialized = False
        return cls._instance
    
    def __init__(self, log_file: str = None):
        """Initialize logger with log file path"""
        if self._initialized:
            return
            
        from .config import Config
        config = Config()
        
        self.log_file = log_file or config.LOG_FILE
        self._ensure_log_file_exists()
        self._initialized = True
    
    def _ensure_log_file_exists(self) -> None:
        """Create log file if it doesn't exist"""
        if not os.path.exists(self.log_file):
            os.makedirs(os.path.dirname(self.log_file), exist_ok=True)
            with open(self.log_file, "w", encoding="utf-8") as f:
                json.dump([], f)
    
    def log_operation(self, file_path: str, operation_type: str, status: str, message: str) -> None:
        """Log an operation to the JSON log file"""
        try:
            # Read current logs
            with open(self.log_file, "r", encoding="utf-8") as f:
                try:
                    logs = json.load(f)
                except json.JSONDecodeError:
                    logs = []
            
            # Add new log entry
            logs.append({
                "timestamp": datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                "file": file_path,
                "operation": operation_type,
                "status": status,
                "message": message
            })
            
            # Limit log size (keep 100 most recent entries)
            if len(logs) > 100:
                logs = logs[-100:]
                
            # Save logs
            with open(self.log_file, "w", encoding="utf-8") as f:
                json.dump(logs, f, indent=2)
        except Exception as e:
            print(f"⚠️ Error writing to log file: {e}")
    
    def get_recent_logs(self, count: int = 10) -> List[Dict[str, Any]]:
        """Get the most recent log entries"""
        try:
            with open(self.log_file, "r", encoding="utf-8") as f:
                logs = json.load(f)
            return logs[-count:] if logs else []
        except Exception:
            return []