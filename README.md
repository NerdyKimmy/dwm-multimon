# My DWM setup

[DWM](https://dwm.suckless.org/) is a dynamic window manager made by the
[Suckless team](). This is my own configuration of this window manager for
few monitors setups.
**Warning: this setup is NOT "just works". You may need to edit some scripts and configs.**

#### Applied patches:
- [single tagset](https://dwm.suckless.org/patches/single_tagset/)
- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/)
- [fadeinactive](https://dwm.suckless.org/patches/fadeinactive/)
- [statusbar on all monitors](https://dwm.suckless.org/patches/statusallmons/)
- my patch for showing playerctl in bar (requires playerctl)
- my patch for normal working floating windows with singletagset 



#### Dependencies:
- playerctl
- dash (for bar script)
- any compositor
- pywal
- maim
- dmenu
- elogind
- feh
- dunst

#### Look:
![looknew](/looknew.png)

- Floating windows work pretty as in other wms like bspwm hyprland i3wm etc

#### Used fonts:

- [JetBrains Mono Nerd Font](https://www.nerdfonts.com/font-downloads)
- DejaVu Sans for flower :3 ✿
- Noto Emojies

## Manual install
#### Pre-installation

- Clone the repository 
- Clone my scripts repository(https://github.com/NerdyKimmy/scripts) and move it to `~/.local/share/scritps`
- Add `export PATH="${HOME}/.local/bin:${PATH}"` to your `~/.bashrc` 
- Edit `dwm/config.h` to change term, fonts, window rules, keybinds, paths etc.
- move dwm dir to ~ and name it `dwm`
- move `walpaper` and `logo` to `~/.local/bin`
#### Installation
```
cd ~/dwm
make install
```
Do NOT execute make as root

Then add this to your `.xinitrc` or create a new session
```
dbus-run-session sh -c '
while true; do
    "$HOME"/dwm/bar.sh &
    BAR_PID=$!
    dwm > "$HOME"/.dwm.log 2>&1
    kill $BAR_PID 2>/dev/null
done
'
```
## Scripted
- Clone repository
```
cd dwm-multimon
chmod +x install.sh
./install.sh
```
-Edit `config.h` and do make install to change term, fonts, window rules, keybinds, paths etc.
## Post-installation
- Change bar output in `~/dwm/bar.sh`.
#### Optionally
- Use logo to get logo as on Screenshot
- Use `walpaper`, my wal script, to get a light theme with an old yellowish book paper atmosphere `walpaper /path/to/your/image`
## Enjoy!
