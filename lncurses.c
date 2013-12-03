#include <stdlib.h>

#include <curses.h>

#include <lua.h>
#include <lauxlib.h>

static const char *LNC_WINDOW_MT = "lnc.window";
static const char *LNC_STDSCR_MT = "lnc.stdscr";

// lncurses.init()
static int lnc_init(lua_State *L)
{
	WINDOW **l_stdscr = lua_newuserdata(L, sizeof(*l_stdscr));
	*l_stdscr = initscr();
	luaL_setmetatable(L, LNC_STDSCR_MT);
	// return stdscr handle
	return 1;
}

// lncurses.quit()
static int lnc_quit(lua_State *L)
{
	endwin();
	return 0;
}

// lncurses.nl(on: boolean)
static int lnc_nl(lua_State *L)
{
	luaL_checktype(L, -1, LUA_TBOOLEAN);
	int on = lua_toboolean(L, -1);
	if (on) {
		nl();
	} else {
		nonl();
	}
	return 0;
}

// lncurses.cbreak(on: boolean)
static int lnc_cbreak(lua_State *L)
{
	luaL_checktype(L, -1, LUA_TBOOLEAN);
	int on = lua_toboolean(L, -1);
	if (on) {
		cbreak();
	} else {
		nocbreak();
	}
	return 0;
}

// lncurses.echo(on: boolean)
static int lnc_echo(lua_State *L)
{
	luaL_checktype(L, -1, LUA_TBOOLEAN);
	int on = lua_toboolean(L, -1);
	if (on) {
		echo();
	} else {
		noecho();
	}
	return 0;
}

// lncurses.raw(on: boolean)
static int lnc_raw(lua_State *L)
{
	luaL_checktype(L, -1, LUA_TBOOLEAN);
	int on = lua_toboolean(L, -1);
	if (on) {
		raw();
	} else {
		noraw();
	}
	return 0;
}

// lncurses.halfdelay(tenths: int)
static int lnc_halfdelay(lua_State *L)
{
	int tenths = luaL_checkint(L, -1);
	tenths = (tenths < 1) ? 1 : tenths;
	tenths = (tenths > 255) ? 255 : tenths;
	halfdelay(tenths);
	return 0;
}

static int lnc_qiflush(lua_State *L)
{
	luaL_checktype(L, -1, LUA_TBOOLEAN);
	int on = lua_toboolean(L, -1);
	if (on) {
		qiflush();
	} else {
		noqiflush();
	}
	return 0;
}

static luaL_Reg lnc_module_fns[] = {
	{"init", &lnc_init},
	{"quit", &lnc_quit},
	{"nl", &lnc_nl},
	{"cbreak", &lnc_cbreak},
	{"echo", &lnc_echo},
	{"raw", &lnc_raw},
	{"halfdelay", &lnc_halfdelay},
	{"qiflush", &lnc_qiflush},
	{NULL, NULL}
};

int luaopen_lncurses(lua_State *L)
{
	// add lncurses module
	luaL_newlib(L, lnc_module_fns);

	return 1;
}