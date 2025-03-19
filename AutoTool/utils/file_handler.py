"""
File handler module for AutoTool
Handles file operations and content manipulation
"""
import os
import shutil
import re
from typing import Optional, List, Tuple


class FileHandler:
    """Handles file operations like reading, writing and content manipulation"""
    
    @staticmethod
    def read_first_comment(file_path: str) -> Optional[str]:
        """Read first line to get target path from comment"""
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                first_line = f.readline().strip()
                # Support both Python and other language comments
                if first_line.startswith("//"):
                    return first_line[2:].strip()  # Remove "//" prefix
                elif first_line.startswith("#"):
                    return first_line[1:].strip()  # Remove "#" prefix
        except UnicodeDecodeError:
            # Try with alternative encoding if utf-8 fails
            try:
                with open(file_path, "r", encoding="latin-1") as f:
                    first_line = f.readline().strip()
                    if first_line.startswith("//"):
                        return first_line[2:].strip()
                    elif first_line.startswith("#"):
                        return first_line[1:].strip()
            except Exception:
                return None
        except Exception:
            return None
        return None

    @staticmethod
    def read_file_content(file_path: str) -> Optional[str]:
        """Read the entire content of a file with encoding fallback"""
        encodings = ["utf-8", "latin-1"]
        
        for encoding in encodings:
            try:
                with open(file_path, "r", encoding=encoding) as f:
                    return f.read()
            except Exception:
                continue
        
        return None

    @staticmethod
    def write_file_content(file_path: str, content: str) -> bool:
        """Write content to a file"""
        try:
            with open(file_path, "w", encoding="utf-8") as f:
                f.write(content)
            return True
        except Exception:
            return False

    @staticmethod
    def remove_line(file_path: str, line_to_remove: str) -> bool:
        """Remove a specific line from a file"""
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                lines = f.readlines()
            
            with open(file_path, "w", encoding="utf-8") as f:
                # Improve matching by removing whitespace
                new_lines = [line for line in lines if line.strip() != line_to_remove.strip()]
                f.writelines(new_lines)
            return True
        except Exception:
            return False

    @staticmethod
    def remove_section_markers(file_path: str) -> bool:
        """Remove status section markers from a file"""
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                lines = f.readlines()
                
            # Find status section boundaries
            start_idx = -1
            end_idx = -1
            
            for i, line in enumerate(lines):
                if line.strip() == "/* AUTO-SYNC STATUS START */":
                    start_idx = i
                elif line.strip() == "/* AUTO-SYNC STATUS END */":
                    end_idx = i
                    
            # If both markers found, remove the section
            if start_idx != -1 and end_idx != -1 and start_idx < end_idx:
                new_lines = lines[:start_idx] + lines[end_idx+1:]
                with open(file_path, "w", encoding="utf-8") as f:
                    f.writelines(new_lines)
            return True
        except Exception:
            return False
            
    @staticmethod
    def copy_file(source: str, destination: str) -> bool:
        """Copy file with directory creation if needed"""
        try:
            dest_dir = os.path.dirname(destination)
            os.makedirs(dest_dir, exist_ok=True)
            shutil.copy2(source, destination)
            return True
        except Exception:
            return False
    
    @staticmethod
    def clean_file(file_path: str) -> bool:
        """Remove commands and status messages from file"""
        try:
            # Remove status section
            FileHandler.remove_section_markers(file_path)
            
            # Remove all types of commands
            with open(file_path, "r", encoding="utf-8") as f:
                lines = f.readlines()
            
            # List of commands to remove
            commands = ["//sync", "#sync", 
                      "//commit now", "#commit now", 
                      "//status", "#status"]
            
            # Add commit patterns to list of commands to remove
            commit_patterns = [
                r"//commit\.", r"#commit\.",
                r"//commit\s+[a-zA-Z0-9_\-\/]+\.", r"#commit\s+[a-zA-Z0-9_\-\/]+\."
            ]
            
            # Filter lines not containing commands
            new_lines = []
            for line in lines:
                should_keep = True
                # Check specific commands
                for cmd in commands:
                    if cmd in line:
                        should_keep = False
                        break
                
                # Check commit patterns
                if should_keep:
                    for pattern in commit_patterns:
                        if re.search(pattern, line):
                            should_keep = False
                            break
                
                if should_keep:
                    new_lines.append(line)
            
            # Write back cleaned content
            with open(file_path, "w", encoding="utf-8") as f:
                f.writelines(new_lines)
                
            return True
        except Exception:
            return False
            
    @staticmethod
    def has_command(content: str, command: str) -> bool:
        """Check if content contains a specific command"""
        return command in content