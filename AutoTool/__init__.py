"""
AutoTool package
Automatically watches for file changes and processes commands
"""
from .utils.config import Config
from .handlers.file_watcher import FileWatcher

__version__ = "1.0.0"