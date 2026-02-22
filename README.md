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
- any compositor (I prefer fastcompmgr)
- pywal
- feh
- dunst

#### Look:
![look](/look.png)

- Floating windows work pretty as in other wms like bspwm hyprland i3wm etc

#### Used fonts:

- [JetBrains Mono Nerd Font](https://www.nerdfonts.com/font-downloads)
- DejaVu Sans for flower :3 ✿

## Pre-installation

- Clone the repository 
- Clone my scripts repository(https://github.com/NerdyKimmy/Scripts) and move it to `~/.local/share/scritps`
- Add `export PATH="${HOME}/.local/bin:${PATH}"` to your `~/.bashrc` 
- Edit `dwm/config.h` to change term, fonts, window rules, keybinds, paths etc.
- move dwm dir to ~ and name it `dwm`
## Installation
```
cd ~/dwm
make install
```
Do NOT execute make as root

Then add this to your `.xinitrc` or create a new session
```
exec startdwm
```

## Post-installation
- Change bar output in `~/dwm/bar.sh`.
- Enjoy!

