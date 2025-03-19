"""
Configuration module for AutoTool
Handles loading and managing configuration settings
"""
import os
import dotenv
from pathlib import Path

class Config:
    """Configuration manager for AutoTool"""
    _instance = None
    
    def __new__(cls):
        """Singleton pattern implementation"""
        if cls._instance is None:
            cls._instance = super(Config, cls).__new__(cls)
            cls._instance._initialized = False
        return cls._instance
    
    def __init__(self):
        """Initialize configuration only once"""
        if self._initialized:
            return
            
        # Find .env file, with fallback - fixing path issue
        script_dir = os.path.dirname(os.path.abspath(__file__))
        autotool_dir = os.path.dirname(script_dir)
        project_root = os.path.dirname(autotool_dir)  # This should now point to /Users/astrelix/Documents/CP
        
        # Load .env file if exists
        env_path = os.path.join(project_root, '.env')
        dotenv.load_dotenv(env_path)
        
        # Directory settings
        self.SCRIPT_DIR = os.getenv('SCRIPT_DIR') or script_dir
        self.WATCH_DIR = os.getenv('WATCH_DIR') or project_root
        
        # File settings - fixing paths
        self.LOG_FILE = os.path.join(project_root, os.getenv('LOG_FILE', 'autosync_log.json'))
        self.TEMPLATE_FILE = os.path.join(project_root, os.getenv('TEMPLATE_FILE', 'AutoTool/template.cpp'))
        
        # General settings
        self.COOLDOWN_PERIOD = float(os.getenv('COOLDOWN_PERIOD', 1))
        self.STATUS_MESSAGE_DURATION = float(os.getenv('STATUS_MESSAGE_DURATION', 2))
        
        self._initialized = True
    
    def ensure_directories_exist(self):
        """Ensure all required directories exist"""
        os.makedirs(os.path.dirname(self.LOG_FILE), exist_ok=True)
        os.makedirs(os.path.dirname(self.TEMPLATE_FILE), exist_ok=True)
        
    def create_template_if_missing(self):
        """Create template file if it doesn't exist"""
        if not os.path.exists(self.TEMPLATE_FILE):
            os.makedirs(os.path.dirname(self.TEMPLATE_FILE), exist_ok=True)
            with open(self.TEMPLATE_FILE, "w", encoding="utf-8") as f:
                f.write("""// Template for Competitive Programming
#include <bits/stdc++.h>
using namespace std;

// Macros
#define ll long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

// Fast I/O
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// Main function
int main() {
    fastIO();
    
    // Your code here
    
    return 0;
}
""")