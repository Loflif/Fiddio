#include "ScriptHandler.h"
#include "LevelHandler.h"

#include <functional>

namespace ScriptHandler
{
	lua_State* Script;

	void Init()
	{
		Script = luaL_newstate();
		luaL_openlibs(Script);
	}

	void CleanUp()
	{
		lua_close(Script);
	}

	bool RegisterFunction(const char* fileName, const char* functionName, lua_CFunction functionWrapper)
	{
		if (!CheckLua(Script, luaL_dofile(Script, fileName)))
			return false;

		lua_register(Script, functionName, functionWrapper);
		return true;
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

	bool GetFunction(const char* fileName, const char* functionName)
	{
		lua_getglobal(Script, functionName);
		if (!lua_isfunction(Script, -1))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, const int functionVariable)
	{
		if (!CheckLua(Script, luaL_dofile(Script, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushinteger(Script, functionVariable);
		if (!CheckLua(Script, lua_pcall(Script, 1, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host)
	{
		if (!CheckLua(Script, luaL_dofile(Script, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(Script, host);
		if (!CheckLua(Script, lua_pcall(Script, 1, 1, 0)))
			return false;

		return true;
	}


	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable)
	{
		if (!CheckLua(Script, luaL_dofile(Script, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(Script, host);
		lua_pushnumber(Script, functionVariable);
		if (!CheckLua(Script, lua_pcall(Script, 1, 1, 0)))
			return false;

		return true;
	}
	
}