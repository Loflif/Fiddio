#pragma once

class lua_State;

namespace ScriptHandler
{
	void Init();
	void CleanUp();

	static int wrap_LoadLevel(lua_State* L);
	static int wrap_SetTile(lua_State* L);
	bool CheckLua(lua_State* L, int r);
	static bool GetFunction(const char* fileName, const char* functionName, const int functionVariable);
	bool CallFunctionNoReturn(const char* fileName, const char* functionName, const int functionVariable);
	bool GetTable(const char* fileName, const char* tableName, const char* variableName);
	const char* GetTableString(const char* fileName, const char* tableName, const char* variableName);
	int GetTableInt(const char* fileName, const char* tableName, const char* variableName);
	float GetTableFloat(const char* fileName, const char* tableName, const char* variableName);
}