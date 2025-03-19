"""
Git handler module for AutoTool
Handles git operations like commit and push
"""
import os
import datetime
import traceback
from typing import Optional

import git

from ..utils.file_handler import FileHandler
from ..utils.status_handler import StatusHandler
from ..utils.logger import Logger
from ..utils.config import Config

class GitHandler:
    """Handles git operations like commit and push"""
    
    def __init__(self):
        """Initialize git handler"""
        self.config = Config()
        self.status_handler = StatusHandler()
        self.logger = Logger()
    
    def get_commit_message(self) -> str:
        """Generate a commit message with timestamp"""
        return f"Auto commit at {datetime.datetime.now().strftime('%H:%M:%S %d/%m/%Y')}"
    
    def commit_changes(self, file_path: str, branch: Optional[str] = None) -> bool:
        """Automatically commit and push changes"""
        try:
            # Find the line where the commit command was issued
            commit_line = -1
            commit_cmd = f"//commit {branch}." if branch else "//commit."
            alt_commit_cmd = f"#commit {branch}." if branch else "#commit."
            
            commit_line = self.status_handler.find_command_line(file_path, commit_cmd)
            if commit_line == -1:
                commit_line = self.status_handler.find_command_line(file_path, alt_commit_cmd)
            
            # Add status message about processing at command location
            if branch:
                self.status_handler.add_inline_status_message(file_path, commit_line, f"Committing to branch '{branch}'...", "info")
            else:
                self.status_handler.add_inline_status_message(file_path, commit_line, "Committing changes...", "info")
            
            repo = git.Repo(self.config.WATCH_DIR)
            
            # Check git status
            if not repo.is_dirty() and len(repo.untracked_files) == 0:
                message = "No changes to commit"
                self.status_handler.add_inline_status_message(file_path, commit_line, message, "info")
                return True
            
            # Save current branch to return to it later
            current_branch = repo.active_branch.name
            
            # Switch to specified branch if provided
            if branch and branch != current_branch:
                try:
                    # Check if branch exists
                    branch_exists = branch in [b.name for b in repo.branches]
                    
                    if not branch_exists:
                        # Create new branch if it doesn't exist
                        repo.git.branch(branch)
                    
                    # Switch to branch
                    repo.git.checkout(branch)
                    
                except Exception as e:
                    error_msg = f"Error switching to branch '{branch}': {str(e)}"
                    self.status_handler.add_inline_status_message(file_path, commit_line, error_msg, "error")
                    
                    # Log error
                    self.logger.log_operation(file_path, "branch_switch", "error", error_msg)
                    return False
            
            # Perform add and commit
            repo.git.add(A=True)  # Add all files
            commit_msg = self.get_commit_message()
            commit = repo.index.commit(commit_msg)
            
            # Get current branch name
            branch_name = repo.active_branch.name
            
            # Push to remote
            try:
                origin = repo.remote(name='origin')
                push_info = origin.push(refspec=f"{branch_name}:{branch_name}")
                
                # Check push result
                if hasattr(push_info[0], 'flags') and push_info[0].flags & push_info[0].ERROR:
                    raise Exception(f"Push failed: {push_info[0].summary}")
                    
                # If successful
                message = f"✅ Committed and pushed to branch '{branch_name}'\n⏱️ {commit_msg}\n📝 SHA: {commit.hexsha[:7]}"
                self.status_handler.add_inline_status_message(file_path, commit_line, message, "success")
                
                # Log successful operation
                self.logger.log_operation(file_path, "commit", "success", 
                                  f"Commit '{commit_msg}' to branch '{branch_name}', SHA: {commit.hexsha[:7]}")
                
            except Exception as e:
                # If push failed but commit succeeded
                error_msg = f"Commit successful but push failed: {str(e)}"
                self.status_handler.add_inline_status_message(file_path, commit_line, error_msg, "error")
                
                # Log error
                self.logger.log_operation(file_path, "push", "error", error_msg)
                
            # Return to original branch if changed
            if branch and branch != current_branch:
                try:
                    repo.git.checkout(current_branch)
                except Exception as e:
                    self.logger.log_operation(file_path, "branch_switch", "error", 
                                       f"Error returning to branch '{current_branch}': {str(e)}")
            
            return True
            
        except Exception as e:
            error_msg = f"Error during commit: {str(e)}"
            self.status_handler.add_status_message(file_path, error_msg, "error")
            traceback.print_exc()
            
            # Log error
            self.logger.log_operation(file_path, "commit", "error", error_msg)
            return False