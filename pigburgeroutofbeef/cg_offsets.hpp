#pragma once

#ifndef cgoffsets
#define cgoffsets

#include "pch.h"

namespace cg
{
	inline DWORD shaderapidx9 = (DWORD)GetModuleHandle("shaderapidx9.dll");


	inline DxGlobal* dx = reinterpret_cast<DxGlobal*>(shaderapidx9 + 0x8A60C);


}

#endif // ! cgoffsets
