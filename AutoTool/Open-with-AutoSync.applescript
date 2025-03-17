tell application "Terminal"
    do script "cd /Users/astrelix/Documents/HSG11 && python3 automatic.py"
end tell

tell application "Visual Studio Code"
    open POSIX file "/Users/astrelix/Documents/HSG11"
    activate
end tell
