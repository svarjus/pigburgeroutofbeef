#pragma once

#ifndef cginit
#define cginit

#include "pch.h"

namespace cg
{
	void CG_GetModules();
	void CG_Init();
	void CG_InitHooks();
	void CG_InitForeverHooks();
	void CG_PrepareHooks();
	void CG_RemoveHooks();
}


#endif