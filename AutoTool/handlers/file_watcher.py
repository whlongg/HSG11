"""
File watcher module for AutoTool
Monitors file changes and triggers command processing
"""
import os
import time
from typing import Dict, Any
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

from ..utils.config import Config
from ..utils.file_handler import FileHandler
from .command_processor import CommandProcessor

class FileEventHandler(FileSystemEventHandler):
    """Handles file system events like modifications"""
    
    def __init__(self):
        """Initialize event handler with required components"""
        self.config = Config()
        self.command_processor = CommandProcessor()
        self.last_modified_time: Dict[str, float] = {}
        
    def on_modified(self, event):
        """Handle file modification events"""
        if event.is_directory:
            return
            
        file_path = event.src_path
        current_time = time.time()
        
        # Skip temporary, hidden, or log files
        if (file_path.endswith(".swp") or file_path.endswith("~") or 
            file_path.endswith(".temp") or os.path.basename(file_path).startswith(".") or 
            file_path == self.config.LOG_FILE):
            return
            
        # Check cooldown period to avoid processing the same file multiple times
        if file_path in self.last_modified_time:
            if current_time - self.last_modified_time[file_path] < self.config.COOLDOWN_PERIOD:
                return  # Skip if file was processed recently
        
        self.last_modified_time[file_path] = current_time
        
        try:
            # Read file content with encoding fallbacks
            content = FileHandler.read_file_content(file_path)
            if content:
                # Process any commands in the file
                self.command_processor.process_command(file_path, content)
        except Exception as e:
            # Silent failure for file reading errors
            pass

class FileWatcher:
    """Watches for file changes in specified directory"""
    
    def __init__(self, watch_dir=None):
        """Initialize the file watcher"""
        self.config = Config()
        self.watch_dir = watch_dir or self.config.WATCH_DIR
        self.event_handler = FileEventHandler()
        self.observer = Observer()
    
    def start(self):
        """Start watching for file changes"""
        self.observer.schedule(self.event_handler, self.watch_dir, recursive=True)
        self.observer.start()
        
        print("🚀 Auto-sync running... (Ctrl+C to stop)")
        print(f"📂 Watching directory: {self.watch_dir}")
        print(f"📝 Log file: {self.config.LOG_FILE}")
        print("📋 Supported commands:")
        print("   - //sync: Synchronize file to destination")
        print("   - //commit.: Commit to current branch")
        print("   - //commit branch_name.: Commit to specified branch")
        print("   - //status: Check synchronization status")
        print("   - //cp: Create competitive programming template")
        print("   - //run: Run C++ compiler")
        
    def stop(self):
        """Stop watching for file changes"""
        self.observer.stop()
        self.observer.join()