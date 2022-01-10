#include "ScriptHandler.h"
#include "LevelHandler.h"

extern "C"
{
#include "../include/lua/lua.h"
#include "../include/lua/lualib.h"
#include "../include/lua/lauxlib.h"
}

#ifdef _WIN64
#pragma comment(lib, "../lib/liblua54.a")
#endif

namespace ScriptHandler
{
	lua_State* Script;

	void Init()
	{
		Script = luaL_newstate();
		luaL_openlibs(Script);

		if (!CheckLua(Script, luaL_dofile(Script, "src/LevelLoader.lua")))
			return;

		lua_register(Script, "_LoadLevel", wrap_LoadLevel);
		lua_register(Script, "_SetTile", wrap_SetTile);
	}

	void CleanUp()
	{
		lua_close(Script);
	}

	static int wrap_LoadLevel(lua_State* L)
	{
		if (lua_gettop(L) != 3) return -1;
		int w = lua_tointeger(L, 1);
		int h = lua_tointeger(L, 2);
		int tileSize = lua_tointeger(L, 3);
		LevelHandler::LoadLevel(w, h, tileSize);
		return 0;
	}

	static int wrap_SetTile(lua_State* L)
	{
		if (lua_gettop(L) != 3) return -1;
		int x = lua_tointeger(L, 1);
		int y = lua_tointeger(L, 2);
		int type = lua_tointeger(L, 3);
		LevelHandler::SetTile(x, y, type);
		return 0;
	}

	bool CheckLua(lua_State* L, int r)
	{
		if (r != LUA_OK)
		{
			std::string errorMsg = lua_tostring(L, -1);
			std::cout << errorMsg << std::endl;
			return false;
		}
		return true;
	}

	bool GetFunction(const char* fileName, const char* functionName, const int functionVariable)
	{
		lua_getglobal(Script, functionName);
		if (!lua_isfunction(Script, -1))
			return false;
		return true;
	}


	bool GetTable(const char* fileName, const char* tableName, const char* variableName)
	{
		lua_getglobal(Script, tableName);
		if (!lua_istable(Script, -1))
		{
			std::cout << "ScriptHandler tried getting table '" << tableName << "' but did not find one" << std::endl;
			return false;
		}
		lua_pushstring(Script, variableName);
		lua_gettable(Script, -2);
	}

	const char* GetTableString(const char* fileName, const char* tableName, const char* variableName)
	{
		if (!CheckLua(Script, luaL_dofile(Script, fileName)))
			return nullptr;

		if (!GetTable(fileName, tableName, variableName))
			return nullptr;

		const char* queriedVariable = lua_tostring(Script, -1);
		lua_pop(Script, 1);
		return queriedVariable;
	}

	int GetTableInt(const char* fileName, const char* tableName, const char* variableName)
	{
		if (!CheckLua(Script, luaL_dofile(Script, fileName)))
			return 0;

		if (!GetTable(fileName, tableName, variableName))
			return 0;

		const int queriedVariable = lua_tointeger(Script, -1);
		lua_pop(Script, 1);
		return queriedVariable;
	}

	float GetTableFloat(const char* fileName, const char* tableName, const char* variableName)
	{
		if (!CheckLua(Script, luaL_dofile(Script, fileName)))
			return 0.0f;

		if (!GetTable(fileName, tableName, variableName))
			return 0.0f;

		const float queriedVariable = lua_tonumber(Script, -1);
		lua_pop(Script, 1);
		return queriedVariable;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, const int functionVariable)
	{
		if (!CheckLua(Script, luaL_dofile(Script, fileName)))
			return false;

		if (!GetFunction(fileName, functionName, functionVariable))
			return false;

		lua_pushinteger(Script, 1);
		if (!CheckLua(Script, lua_pcall(Script, 1, 1, 0)))
			return false;

		return true;
	}
}