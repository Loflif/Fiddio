#pragma once
#include "LuaIncludes.h"

namespace ScriptHandler
{
	void Init();
	void CleanUp();

	bool CheckLua(lua_State* L, int r);
	bool RegisterFunction(const char* fileName, const char* functionName, lua_CFunction functionWrapper);
	bool GetFunction(const char* fileName, const char* functionName);
	bool CallFunctionNoReturn(const char* fileName, const char* functionName, const int functionVariable);
	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host);
	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable);
	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable, const bool functionVariable2);
	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable, const float functionVariable2);
	bool CallFunctionNoReturn(const char* fileName, const char* functionName, void* host, const double functionVariable, const float functionVariable2, const float functionVariable3);
	bool GetTable(const char* fileName, const char* tableName, const char* variableName);
	const char* GetTableString(const char* fileName, const char* tableName, const char* variableName);
	int GetTableInt(const char* fileName, const char* tableName, const char* variableName);
	float GetTableFloat(const char* fileName, const char* tableName, const char* variableName);
}