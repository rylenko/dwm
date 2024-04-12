/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define TERM "st-256color"
#define TERM_CLASS "st-256color"

/* appearance */
static unsigned int baralpha = 0xd0;
static unsigned int borderalpha = OPAQUE;
/* border pixel of windows */
static const unsigned int borderpx = 3;
static const unsigned int gappx = 15;
/* snap pixel */
static const unsigned int snap = 32;
/* 1 means swallow floating windows by default */
static const int swallowfloating = 0;
/* 0 means no bar */
static const int showbar = 1;
/* 0 means bottom bar */
static const int topbar = 1;
static const char *fonts[] = {
	"Iosevka Nerd Font Mono:style=Regular:size=9",
	"Noto Color Emoji:style=Regular:size=11",
};
static const char barfg[] = "#bbbbbb";
static const char barbg[] = "#000000";
static const char barborder[] = "#000000";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#bbbbbb", "#222222", "#444444" },
	[SchemeSel] = { "#eeeeee", "#005577", barfg  },
	[SchemeStatus] = { barfg, barbg, barborder },
	[SchemeTagsSel] = { barfg, barbg, barborder },
	[SchemeTagsNorm] = { barfg, barbg, barborder },
	[SchemeInfoSel] = { barfg, barbg, barborder },
	[SchemeInfoNorm] = { barfg, barbg, barborder },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *      WM_CLASS(STRING) = instance, class
	 *      WM_NAME(STRING) = title
	 */
	/* class      inst  title           tags isfloat isterm noswallow monitor */
	{ TERM_CLASS, NULL, NULL,           0,   0,      1,     0,        -1 },
	{ "Display",  NULL, NULL,           0,   1,      0,     0,        -1 },
	{ "mpv",      NULL, NULL,           3,   0,      0,     0,        -1 },
	{ NULL,       NULL, "Event Tester", 0,   0,      0,     1,        -1 },
};

/* layout(s) */
/* factor of master area size [0.05..0.95] */
static const float mfact = 0.55;
/* number of clients in master area */
static const int nmaster = 1;
/* 1 means respect size hints in tiled resizals */
static const int resizehints = 0;
/* 1 will force focus on the fullscreen window */
static const int lockfullscreen = 1;

static const Layout layouts[] = {
	/* symbol arrange function */
	{ "[]=",  tile }, /* first entry is default */
	{ "><>",  NULL }, /* no layout function means floating behavior */
	{ "[M]",  monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY, view,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG} },

/* commands */
static const char *browsercmd[] = { TERM, "-e", "w3m", NULL };
static const char *dmenucleansyscmd[] = { "dmenu-clean-sys", NULL };
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *dmenuhandlelinkcmd[] = { "dmenu-handle-link", NULL };
static const char *getappclscmd[] = { "get-app-cls", NULL };
static const char *netstartcmd[] = { "doas", "sh", "/etc/netstart", NULL };
static const char *makescreenshotcmd[] = { "make-screenshot", NULL };
static const char *pkillherbecmd[] = { "pkill", "-SIGUSR1", "herbe", NULL };
static const char *signalsndioblockcmd[] = {
	"pkill", "-SIGUSR1", "dwmblocks", NULL,
};
static const char *slockcmd[] = { "slock", NULL };
static const char *rebootcmd[] = { "doas", "reboot", NULL };
static const char *setwpcmd[] = { "dmenu-set-wp", NULL };
static const char *sfeedcursescmd[] = {
	"sh", "-c", TERM " -e sfeed_curses ~/.sfeed/feeds/*", NULL,
};
static const char *shutdowncmd[] = {
	"doas", "shutdown", "-p", "now", NULL,
};
static const char *termcmd[] = { TERM, NULL };
static const char *updfeedscmd[] = { "upd-feeds", NULL };

/* keys */
#include "movestack.c"
static const Key keys[] = {
	/* modifier         key        function        argument */
	{ MODKEY,           XK_a,      spawn,          {.v = getappclscmd} },
	{ MODKEY,           XK_b,      togglebar,      {0} },
	{ MODKEY,           XK_d,      spawn,          {.v = dmenucmd} },
	{ MODKEY,           XK_f,      fullscreen,     {0} },
	{ MODKEY|ShiftMask, XK_f,      togglefloating, {0} },
	{ MODKEY,           XK_g,      setgaps,        {.i = -1} },
	{ MODKEY|ShiftMask, XK_g,      setgaps,        {.i = +1} },
	{ MODKEY,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_j,      focusstack,     {.i = +1} },
	{ MODKEY|ShiftMask, XK_j,      movestack,      {.i = +1} },
	{ MODKEY,           XK_i,      incnmaster,     {.i = +1} },
	{ MODKEY|ShiftMask, XK_i,      incnmaster,     {.i = -1} },
	{ MODKEY,           XK_k,      focusstack,     {.i = -1} },
	{ MODKEY|ShiftMask, XK_k,      movestack,      {.i = -1} },
	{ MODKEY,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_n,      spawn,          {.v = pkillherbecmd} },
	{ MODKEY|ShiftMask, XK_n,      spawn,          {.v = netstartcmd} },
	{ MODKEY,           XK_o,      spawn,          {.v = dmenucleansyscmd} },
	{ MODKEY,           XK_p,      spawn,          {.v = shutdowncmd} },
	{ MODKEY|ShiftMask, XK_p,      spawn,          {.v = rebootcmd} },
	{ MODKEY,           XK_s,      spawn,          {.v = sfeedcursescmd} },
	{ MODKEY,           XK_u,      spawn,          {.v = dmenuhandlelinkcmd} },
	{ MODKEY|ShiftMask, XK_u,      spawn,          {.v = updfeedscmd} },
	{ MODKEY,           XK_w,      spawn,          {.v = browsercmd} },
	{ MODKEY|ShiftMask, XK_w,      spawn,          {.v = setwpcmd} },
	{ MODKEY,           XK_Return, spawn,          {.v = termcmd} },
	{ MODKEY,           XK_Return, zoom,           {0} },
	{ MODKEY,           XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask, XK_slash,  killclient,     {0} },
	{ MODKEY,           XK_space,  setlayout,      {0} },
	{ MODKEY,           XK_comma,  focusmon,       {.i = -1} },
	{ MODKEY,           XK_period, focusmon,       {.i = +1} },
	{ MODKEY|ShiftMask, XK_comma,  tagmon,         {.i = -1} },
	{ MODKEY|ShiftMask, XK_period, tagmon,         {.i = +1} },
	{ MODKEY|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY,           XK_0,      view,           {.ui = ~0} },
	{ MODKEY|ShiftMask, XK_0,      tag,            {.ui = ~0} },
	TAGKEYS(            XK_1,                      0)
	TAGKEYS(            XK_2,                      1)
	TAGKEYS(            XK_3,                      2)
	TAGKEYS(            XK_4,                      3)
	TAGKEYS(            XK_5,                      4)
	TAGKEYS(            XK_6,                      5)
	TAGKEYS(            XK_7,                      6)
	TAGKEYS(            XK_8,                      7)
	TAGKEYS(            XK_9,                      8)
	{ MODKEY,           XK_F2,    spawn,           {.v = slockcmd} },
	{ MODKEY,           XK_Print, spawn,           {.v = makescreenshotcmd} },
	/*
	My "Thinkpad" itself (in/de)creases the audio volume when this
	keys are pressed (`acpithinkpad(4)` on "OpenBSD"), so just send
	signal to sndio block.

	"OpenBSD"'s `acpithinkpad(4)` does not handle "Thinkpad"'s mute button,
	but it works internally..
	*/
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = signalsndioblockcmd} },
	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = signalsndioblockcmd} },
};

/* button definitions */
/*
click can be:
- ClkTagBar
- ClkLtSymbol
- ClkStatusText
- ClkWinTitle
- ClkClientWin
- ClkRootWin
*/
static const Button buttons[] = {
	/* click         event   button   function        argument */
	{ ClkLtSymbol,   0,      Button1, setlayout,      {0} },
	{ ClkLtSymbol,   0,      Button3, setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,   0,      Button2, zoom,           {0} },
	{ ClkStatusText, 0,      Button2, spawn,          {.v = termcmd } },
	{ ClkClientWin,  MODKEY, Button1, movemouse,      {0} },
	{ ClkClientWin,  MODKEY, Button2, togglefloating, {0} },
	{ ClkClientWin,  MODKEY, Button3, resizemouse,    {0} },
	{ ClkTagBar,     0,      Button1, view,           {0} },
	{ ClkTagBar,     0,      Button3, toggleview,     {0} },
	{ ClkTagBar,     MODKEY, Button1, tag,            {0} },
	{ ClkTagBar,     MODKEY, Button3, toggletag,      {0} },
};

