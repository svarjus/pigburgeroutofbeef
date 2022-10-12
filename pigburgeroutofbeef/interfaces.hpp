#pragma once

#ifndef __interfaces
#define __interfaces

#include "pch.h"


template <typename T>
T* GetInterface(const char* name, const char* library)
{
	const auto handle = GetModuleHandleA(library);

	if (!handle)
		return nullptr;

	const auto fnc = GetProcAddress(handle, "CreateInterface");

	if (!fnc)
		return nullptr;

	return reinterpret_cast<T * (*)(const char*, DWORD*)>(fnc)(name, nullptr);


}
namespace interfaces
{
	const char* const EngineTraceClient004 = "EngineTraceClient004"; // engine
	const char* const VEngineClient014 = "VEngineClient014"; //engine
	const char* const VModelInfoClient004 = "VModelInfoClient004"; //engine
	const char* const VClientEntityList003 = "VClientEntityList003"; //client

	inline IEngineTrace* engineTrace = GetInterface<IEngineTrace>(EngineTraceClient004, "engine.dll");
	//inline auto entityList = GetInterface<IClientEntityList>(VClientEntityList003, "client.dll");
	//inline auto local = GetInterface<IVEngineClient013>(VEngineClient014, "engine.dll");
	//inline auto modelInfo = GetInterface<ModelInfo>(VModelInfoClient004, "engine.dll");
};


#endif