#include "ScriptHandler.h"
#include "LevelHandler.h"

namespace ScriptHandler
{
	lua_State* State;

	void Init()
	{
		State = luaL_newstate();
		luaL_openlibs(State);
	}

	void CleanUp()
	{
		lua_close(State);
	}

	bool RegisterFunction(const char* fileName, const char* functionName, lua_CFunction functionWrapper)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		lua_register(State, functionName, functionWrapper);
		return true;
	}

	bool CheckLua(lua_State* state, int response)
	{
		if (response != LUA_OK)
		{
			std::string errorMsg = lua_tostring(state, -1);
			std::cout << errorMsg << std::endl;
			return false;
		}
		return true;
	}

	
	bool GetTable(const char* fileName, const char* tableName, const char* variableName)
	{
		lua_getglobal(State, tableName);
		if (!lua_istable(State, -1))
		{
			std::cout << "ScriptHandler tried getting table '" << tableName << "' but did not find one" << std::endl;
			return false;
		}
		lua_pushstring(State, variableName);
		lua_gettable(State, -2);
	}

	const char* GetTableString(const char* fileName, const char* tableName, const char* variableName)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return nullptr;

		if (!GetTable(fileName, tableName, variableName))
			return nullptr;

		const char* queriedVariable = lua_tostring(State, -1);
		lua_pop(State, 1);
		return queriedVariable;
	}

	int GetTableInt(const char* fileName, const char* tableName, const char* variableName)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return 0;

		if (!GetTable(fileName, tableName, variableName))
			return 0;

		const int queriedVariable = lua_tointeger(State, -1);
		lua_pop(State, 1);
		return queriedVariable;
	}

	float GetTableFloat(const char* fileName, const char* tableName, const char* variableName)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return 0.0f;

		if (!GetTable(fileName, tableName, variableName))
			return 0.0f;

		const float queriedVariable = lua_tonumber(State, -1);
		lua_pop(State, 1);
		return queriedVariable;
	}

	bool GetFunction(const char* fileName, const char* functionName)
	{
		lua_getglobal(State, functionName);
		if (!lua_isfunction(State, -1))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		if (!CheckLua(State, lua_pcall(State, 0, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, const int functionVariable)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushinteger(State, functionVariable);
		if (!CheckLua(State, lua_pcall(State, 1, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(State, host);
		if (!CheckLua(State, lua_pcall(State, 1, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable, const float functionVariable2)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(State, host);
		lua_pushnumber(State, functionVariable);
		lua_pushnumber(State, functionVariable2);
		if (!CheckLua(State, lua_pcall(State, 3, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable, const float functionVariable2, const float functionVariable3)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(State, host);
		lua_pushnumber(State, functionVariable);
		lua_pushnumber(State, functionVariable2);
		lua_pushnumber(State, functionVariable3);
		if (!CheckLua(State, lua_pcall(State, 4, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable, const float functionVariable2, const float functionVariable3, const int functionVariable4)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(State, host);
		lua_pushnumber(State, functionVariable);
		lua_pushnumber(State, functionVariable2);
		lua_pushnumber(State, functionVariable3);
		lua_pushinteger(State, functionVariable4);
		if (!CheckLua(State, lua_pcall(State, 5, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const float functionVariable, const float functionVariable2, const float functionVariable3, const float functionVariable4, const int functionVariable5)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(State, host);
		lua_pushnumber(State, functionVariable);
		lua_pushnumber(State, functionVariable2);
		lua_pushnumber(State, functionVariable3);
		lua_pushnumber(State, functionVariable4);
		lua_pushinteger(State, functionVariable5);
		if (!CheckLua(State, lua_pcall(State, 6, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(State, host);
		lua_pushnumber(State, functionVariable);
		if (!CheckLua(State, lua_pcall(State, 2, 1, 0)))
			return false;

		return true;
	}

	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable, const bool functionVariable2)
	{
		if (!CheckLua(State, luaL_dofile(State, fileName)))
			return false;

		if (!GetFunction(fileName, functionName))
			return false;

		lua_pushlightuserdata(State, host);
		lua_pushnumber(State, functionVariable);
		lua_pushboolean(State, functionVariable2);
		if (!CheckLua(State, lua_pcall(State, 3, 1, 0)))
			return false;

		return true;
	}
	
}