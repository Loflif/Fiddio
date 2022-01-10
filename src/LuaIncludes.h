#pragma once

extern "C"
{
#include "../include/lua/lua.h"
#include "../include/lua/lualib.h"
#include "../include/lua/lauxlib.h"
}

#ifdef _WIN64
#pragma comment(lib, "../lib/liblua54.a")
#endif
