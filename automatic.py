#!/usr/bin/env python3
"""
AutoTool - Automatic file synchronization, git management, and more for competitive programming
"""
import os
import sys
import time
import signal

# Add the project root to path to ensure imports work correctly
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

try:
    from AutoTool.utils.config import Config
    from AutoTool.handlers.file_watcher import FileWatcher
except ImportError as e:
    print(f"⚠️ Error importing AutoTool modules: {e}")
    print("Make sure you've installed all requirements with: pip install -r requirements.txt")
    sys.exit(1)

def main():
    """Main function to start AutoTool"""
    # Initialize configuration
    config = Config()
    
    # Ensure necessary directories and files exist
    config.ensure_directories_exist()
    config.create_template_if_missing()
    
    # Start file watcher
    watcher = FileWatcher()
    
    # Handle graceful shutdown
    def signal_handler(sig, frame):
        print("\n🛑 Stopping AutoTool...")
        watcher.stop()
        print("✅ Stopped successfully")
        sys.exit(0)
    
    # Register signal handlers for Ctrl+C
    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)
    
    try:
        watcher.start()
        # Keep the main thread alive
        while True:
            time.sleep(1)
    except Exception as e:
        print(f"⚠️ Error: {str(e)}")
        watcher.stop()
        sys.exit(1)

if __name__ == "__main__":
    main()