/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {
    "JetBrainsMono Nerd Font:size=12",
    "DejaVu Sans:size=14",     // Secondary/Fallback font
};
static const char dmenufont[]       = "monospace:size=10";
/* tagging */
#include <X11/XF86keysym.h>
#include "/home/aliisa/.cache/wal/colors-wal-dwm.h"
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Telegram", NULL,       NULL,       1 << 5,        1,           -1 },
	{ "krita",    NULL,       NULL,       1 <<  4,        1,           -1 },
	{ "mpv",      NULL,       NULL,       0,             1,           -1 },
	{ "imv",      NULL,       NULL,       0,             1,           -1 },
	{ "emacs",    NULL,       NULL,       0,             1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const double activeopacity   = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 0.92f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity       = True;     /* Starts with opacity on any unfocused windows */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "󱂬",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// apps
static const char *termcmd[]     = { "st", NULL };
static const char *firefox[]     = { "firefox", NULL };
static const char *thunar[]      = { "thunar", NULL };
// scripts
static const char *dmenucmd[]    = {"/home/aliisa/.local/share/scripts/dmenu.sh", NULL };
static const char *player[]      = { "/home/aliisa/.local/share/scripts/player.sh", NULL };
static const char *prev[]        = { "/home/aliisa/.local/share/scripts/prev.sh", NULL };
static const char *next[]        = { "/home/aliisa/.local/share/scripts/next.sh", NULL };
static const char *rewal[]       = { "/home/aliisa/.local/share/scripts/waldwm.sh", NULL };
static const char *screenshot[]  = { "/home/aliisa/.local/share/scripts/screenshot.sh", NULL };
static const char *screenshotf[] = { "/home/aliisa/.local/share/scripts/screenshotfull.sh", NULL };
static const char *powermenu[]   = { "/home/aliisa/.local/share/scripts/powermenu.sh", NULL };
static const char *lock[]        = { "/home/aliisa/.local/share/scripts/lockf.sh", NULL };
static const char *lastscr[]     = { "/home/aliisa/.local/share/scripts/lastscreen.sh", NULL };
//audio
static const char *upvol[]       = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+4%",     NULL };
static const char *downvol[]     = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-4%",     NULL };
static const char *mutevol[]     = { "/usr/bin/pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = firefox} },
	{ MODKEY,                       XK_Escape, spawn,          {.v = powermenu} },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = lastscr} },
	{ MODKEY|ShiftMask,             XK_Escape, spawn,          {.v = lock} },
	{ MODKEY,                       XK_p,      spawn,          {.v = player} },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = prev } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = next } },
	{ MODKEY,                       XK_f,      spawn,          {.v = thunar} },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,                       XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab, zoom,           {0} },
	{ MODKEY|ShiftMask,                       XK_y,    view,           {0} },
	{ MODKEY,             XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,             XK_s,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ 0,                            XF86XK_AudioRaiseVolume,     spawn,          {.v = upvol   } },
	{ 0,                            XF86XK_AudioLowerVolume,     spawn,          {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,            spawn,          {.v = mutevol } },
	{ 0,                            XK_Print,  spawn,          {.v = screenshot} },
	{ ShiftMask,                    XK_Print,  spawn,          {.v = screenshotf} },
	{ MODKEY|Mod1Mask,              XK_r,      spawn,          {.v = rewal} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

