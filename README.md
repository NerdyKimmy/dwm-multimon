# DWM MultiMon

[DWM](https://dwm.suckless.org/) is a dynamic window manager made by the
[Suckless team](https://suckless.org/). This is my own configuration of this window manager for
multiple monitor setups.
**Warning: this setup is NOT "just works". You may need to edit some scripts and configs.**

#### Changes compared to vanilla:
- Floating windows are spawned in the center and can be moved like in BSPWM through all monitors
- Single tags for multiple monitors, now monitor's clients are not a separate list for each
- Live tag swap functional with moving both floating and tiled X clients
- Built-in inactive windows fade, can be used with any compositor
- Bar is presented on all screens (Script with bar setup is built-in)
- Music on bar instead of current focused window, can be used with moc and with playerctl (bar.sh and dbusbar.sh scripts)
- Fixed bugs with transparent window's border

#### Dependencies:
- playerctl (only for dbus script version)
- dash (for bar script)
- any compositor (optional)
- pywal
- maim
- elogind (only for playerctl)
- feh
- herbe (can be replaced with dunst, if you prefer to use dbus)

##### Also included:
- dmenu (my build)
- wallpaper (script for such a light colorscheme with yellowish bg color instead of white for an old library atmosphere)

#### Look:
![looknew](/looknew.png)

- Floating windows work pretty much as in other wms 

#### Used fonts:

- [JetBrains Mono Nerd Font](https://www.nerdfonts.com/font-downloads)
- DejaVu Sans for flower ✿
- Noto Emojis

## Manual install
#### Pre-installation

- Clone the repository 
- Clone my scripts repository (https://github.com/NerdyKimmy/scripts) and move it to `~/.local/share/scripts`
- Add `export PATH="${HOME}/.local/bin:${PATH}"` to your `~/.bashrc` 
- Edit `dwm/config.h` to change term, fonts, window rules, keybinds, paths etc.
- Move dwm dir to `~` and name it `dwm`
- Move `wallpaper` and `logo` to `~/.local/bin`

#### Installation
```bash
cd ~/dwm
make install
```
*Note: Do NOT execute make as root if your `config.mk` is set up to install in a local user directory.*

Then add this to your `.xinitrc` (or `.desktop` file if using a display manager) or create a new session:
```bash
dbus-run-session sh -c '
while true; do
    "$HOME"/dwm/bar.sh &
    BAR_PID=$!
    dwm > "$HOME"/.dwm.log 2>&1
    kill $BAR_PID 2>/dev/null
done
'
```
*(Remove `dbus-run-session` from the snippet if you prefer not to use it).*

## Scripted
- Clone repository
```bash
cd dwm-multimon
chmod +x install.sh
```
- Edit `config.h` to change term, fonts, window rules, keybinds, paths etc., then install:
```bash
./install.sh
make install
```

## Post-installation
- Change bar output in `~/dwm/bar.sh`.

#### Optionally
- Use `wallpaper`, my wal script, to get a light theme with an old yellowish book paper atmosphere: `wallpaper /path/to/your/image`

## Enjoy!
