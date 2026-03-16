#!/bin/sh

mkdir -p "$HOME/.local/bin"

SCRIPTS_DIR="$HOME/.local/share/scripts"

if [ ! -d "$SCRIPTS_DIR" ]; then
    printf "Cloning scripts repository...\n"
    mkdir -p "$HOME/.local/share"
    git clone https://github.com/NerdyKimmy/Scripts "$SCRIPTS_DIR"
else
    printf "Scripts directory already exists. Skipping clone.\n"
fi

PATH_LINE='export PATH="${HOME}/.local/bin:${PATH}"'

for rc in .bashrc .zshrc .mkshrc .yashrc .profile .bash_profile .kshrc; do
    TARGET="$HOME/$rc"
    if [ -f "$TARGET" ]; then
        # Check if the line already exists to avoid duplicates
        if ! grep -Fx "$PATH_LINE" "$TARGET" > /dev/null 2>&1; then
            printf "Adding PATH to %s...\n" "$TARGET"
            printf "\n# Local bin path\n%s\n" "$PATH_LINE" >> "$TARGET"
        else
            printf "PATH already exists in %s.\n" "$TARGET"
        fi
    fi
done

for file in walpaper logo; do
    if [ -f "$file" ]; then
        printf "Moving %s to ~/.local/bin...\n" "$file"
        mv "$file" "$HOME/.local/bin/"
    else
        printf "Warning: File '%s' not found in current directory.\n" "$file"
    fi
done

if [ -d "dwm" ]; then
    printf "Moving dwm directory to %s/dwm...\n" "$HOME"
    cp -r dwm "$HOME/dwm"
    printf "Note: Please edit %s/dwm/config.h for your settings before building.\n" "$HOME"
else
    printf "Error: 'dwm' directory not found in the current folder.\n"
    exit 1
fi

# --- Installation ---

printf "Building and installing dwm...\n"
cd "$HOME/dwm" || exit 1

make
make install


XINITRC="$HOME/.xinitrc"
printf "Configuring %s...\n" "$XINITRC"

# Ensure .xinitrc exists
touch "$XINITRC"

# Append the session loop
cat << 'EOF' >> "$XINITRC"

# dwm session loop
dbus-run-session sh -c '
while true; do
    "$HOME"/dwm/bar.sh &
    BAR_PID=$!
    dwm > "$HOME"/.dwm.log 2>&1
    kill $BAR_PID 2>/dev/null
done
'
EOF

printf "Installation complete!\n"
printf "Post-installation: Change bar output in ~/dwm/bar.sh and enjoy!\n"
