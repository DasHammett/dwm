--- config.def.h	2022-01-07 12:42:18.000000000 +0100
+++ patches/config.def.h	2022-01-21 14:15:50.902250091 +0100
@@ -3,9 +3,15 @@
 /* appearance */
 static const unsigned int borderpx  = 1;        /* border pixel of windows */
 static const unsigned int snap      = 32;       /* snap pixel */
+static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
+static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
+static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
+static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
+static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
+static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
 static const int showbar            = 1;        /* 0 means no bar */
 static const int topbar             = 1;        /* 0 means bottom bar */
-static const char *fonts[]          = { "monospace:size=10" };
+static const char *fonts[]          = {"JetBrainsMono Nerd Font:size=9" };
 static const char dmenufont[]       = "monospace:size=10";
 static const char col_gray1[]       = "#222222";
 static const char col_gray2[]       = "#444444";
@@ -19,33 +25,50 @@
 };
 
 /* tagging */
-static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
+static const char *tags[] = { "1", "2", "3", "4"};
 
 static const Rule rules[] = {
 	/* xprop(1):
 	 *	WM_CLASS(STRING) = instance, class
 	 *	WM_NAME(STRING) = title
 	 */
-	/* class      instance    title       tags mask     isfloating   monitor */
-	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
-	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
+	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
+	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
+	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
+	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
+	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
 };
 
 /* layout(s) */
-static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
+static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
 static const int nmaster     = 1;    /* number of clients in master area */
-static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
+static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
 static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
 
+#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
+#include "vanitygaps.c"
+
 static const Layout layouts[] = {
 	/* symbol     arrange function */
 	{ "[]=",      tile },    /* first entry is default */
-	{ "><>",      NULL },    /* no layout function means floating behavior */
 	{ "[M]",      monocle },
+	{ "[@]",      spiral },
+	{ "[\\]",     dwindle },
+	{ "H[]",      deck },
+	{ "TTT",      bstack },
+	{ "===",      bstackhoriz },
+	{ "HHH",      grid },
+	{ "###",      nrowgrid },
+	{ "---",      horizgrid },
+	{ ":::",      gaplessgrid },
+	{ "|M|",      centeredmaster },
+	{ ">M>",      centeredfloatingmaster },
+	{ "><>",      NULL },    /* no layout function means floating behavior */
+	{ NULL,       NULL },
 };
 
 /* key definitions */
-#define MODKEY Mod1Mask
+#define MODKEY Mod4Mask
 #define TAGKEYS(KEY,TAG) \
 	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
 	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
@@ -55,46 +78,88 @@
 /* helper for spawning shell commands in the pre dwm-5.0 fashion */
 #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
 
+#define STATUSBAR "dwmblocks"
+
 /* commands */
 static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
-static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
+static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
+static const char *rofirun[] = { "rofi", "-show", "run", NULL };
 static const char *termcmd[]  = { "st", NULL };
 
+#include <X11/XF86keysym.h>
+static const char *upvol[] = {"sb-volumeup","up",NULL};
+static const char *downvol[] = {"sb-volumeup","down",NULL};
+static const char *mute[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
+static const char *prev[] = { "mpc", "prev", NULL };
+static const char *next[] = { "mpc", "next", NULL };
+static const char *toggle[] = { "mpc", "toggle",NULL };
+
+
+
+
 static Key keys[] = {
 	/* modifier                     key        function        argument */
-	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
-	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
-	{ MODKEY,                       XK_b,      togglebar,      {0} },
-	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
-	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
-	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
-	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
-	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
-	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
-	{ MODKEY,                       XK_Return, zoom,           {0} },
-	{ MODKEY,                       XK_Tab,    view,           {0} },
-	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
-	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
-	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
-	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
-	{ MODKEY,                       XK_space,  setlayout,      {0} },
-	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
-	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
-	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
-	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
-	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
-	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
-	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
-	TAGKEYS(                        XK_1,                      0)
-	TAGKEYS(                        XK_2,                      1)
-	TAGKEYS(                        XK_3,                      2)
-	TAGKEYS(                        XK_4,                      3)
-	TAGKEYS(                        XK_5,                      4)
-	TAGKEYS(                        XK_6,                      5)
-	TAGKEYS(                        XK_7,                      6)
-	TAGKEYS(                        XK_8,                      7)
-	TAGKEYS(                        XK_9,                      8)
-	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
+	{ MODKEY,                       XK_d,                       spawn,          {.v = dmenucmd } },
+	{ MODKEY,                       XK_s,                       spawn,          {.v = rofirun } },
+	{ MODKEY,                       XK_Return,                  spawn,          {.v = termcmd } },
+	{ MODKEY,                       XK_b,                       togglebar,      {0} },
+	{ MODKEY,                       XK_j,                       focusstack,     {.i = +1 } },
+	{ MODKEY,                       XK_k,                       focusstack,     {.i = -1 } },
+	{ MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
+	{ MODKEY,                       XK_p,                       incnmaster,     {.i = -1 } },
+	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
+	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
+	{ MODKEY|ShiftMask,             XK_h,                       setcfact,       {.f = +0.05} },
+	{ MODKEY|ShiftMask,             XK_l,                       setcfact,       {.f = -0.05} },
+	{ MODKEY|ShiftMask,             XK_o,                       setcfact,       {.f =  0.00} },
+	{ MODKEY|ShiftMask,             XK_Return,                  zoom,           {0} },
+	{ MODKEY|Mod4Mask,              XK_u,                       incrgaps,       {.i = +1 } },
+	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,                       incrgaps,       {.i = -1 } },
+	{ MODKEY|Mod4Mask,              XK_i,                       incrigaps,      {.i = +1 } },
+	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,                       incrigaps,      {.i = -1 } },
+	{ MODKEY|Mod4Mask,              XK_o,                       incrogaps,      {.i = +1 } },
+	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,                       incrogaps,      {.i = -1 } },
+	{ MODKEY|Mod4Mask,              XK_6,                       incrihgaps,     {.i = +1 } },
+	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,                       incrihgaps,     {.i = -1 } },
+	{ MODKEY|Mod4Mask,              XK_7,                       incrivgaps,     {.i = +1 } },
+	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,                       incrivgaps,     {.i = -1 } },
+	{ MODKEY|Mod4Mask,              XK_8,                       incrohgaps,     {.i = +1 } },
+	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,                       incrohgaps,     {.i = -1 } },
+	{ MODKEY|Mod4Mask,              XK_9,                       incrovgaps,     {.i = +1 } },
+	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,                       incrovgaps,     {.i = -1 } },
+	{ MODKEY|Mod4Mask,              XK_0,                       togglegaps,     {0} },
+	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,                       defaultgaps,    {0} },
+	{ MODKEY,                       XK_Tab,                     view,           {0} },
+	{ MODKEY|ShiftMask,             XK_q,                       killclient,     {0} },
+	{ MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },
+	{ MODKEY,                       XK_f,                       setlayout,      {.v = &layouts[1]} },
+	{ MODKEY,                       XK_m,                       setlayout,      {.v = &layouts[2]} },
+	{ MODKEY,                       XK_space,                   setlayout,      {0} },
+	{ MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
+	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
+	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
+	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
+	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
+	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
+	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
+	TAGKEYS(                        XK_1,                                       0)
+	TAGKEYS(                        XK_2,                                       1)
+	TAGKEYS(                        XK_3,                                       2)
+	TAGKEYS(                        XK_4,                                       3)
+	TAGKEYS(                        XK_5,                                       4)
+	TAGKEYS(                        XK_6,                                       5)
+	TAGKEYS(                        XK_7,                                       6)
+	TAGKEYS(                        XK_8,                                       7)
+	TAGKEYS(                        XK_9,                                       8)
+	{ MODKEY|ShiftMask,             XK_c,                       quit,           {0} },
+    { 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = upvol } },
+    { 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = downvol } },
+    { 0,                            XF86XK_AudioMute,           spawn,          {.v = mute } },
+    { 0,                            XK_F7,                      spawn,          {.v = prev } },
+    { 0,                            XK_F8,                      spawn,          {.v = toggle } },
+    { 0,                            XK_F9,                      spawn,          {.v = next } },
+    {MODKEY|ShiftMask,              XK_x,                       spawn,          SHCMD("shutdown -h now")},
+    {MODKEY|ShiftMask,              XK_z,                       spawn,          SHCMD("shutdown -r now")},
 };
 
 /* button definitions */
@@ -104,7 +169,9 @@
 	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
 	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
 	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
-	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
+	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
+	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
+	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
 	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
 	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
 	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
