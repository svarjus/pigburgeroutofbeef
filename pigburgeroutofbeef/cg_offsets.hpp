#pragma once

#ifndef cgoffsets
#define cgoffsets

#include "pch.h"

namespace cg
{
	inline DWORD shaderapidx9 = (DWORD)GetModuleHandle("shaderapidx9.dll");
	inline DWORD client_module = (DWORD)GetModuleHandle("client.dll");
	inline DWORD engine_module = (DWORD)GetModuleHandle("engine.dll");
	inline DWORD localPplayer_module = client_module + dwLocalPlayer;
	inline DWORD server_module = (DWORD)GetModuleHandle("server.dll");

	inline DxGlobal dx;
	inline vmatrix* viewMatrix = reinterpret_cast<vmatrix*>(client_module + dwViewMatrix);
	inline GlobalVars* globalVars = reinterpret_cast<GlobalVars*>(engine_module + 0x58CCE0);

}

#endif // ! cgoffsets
