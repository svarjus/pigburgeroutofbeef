#pragma once

#ifndef cgoffsets
#define cgoffsets

#include "pch.h"

namespace cg
{
	inline DWORD shaderapidx9 = (DWORD)GetModuleHandle("shaderapidx9.dll");


	inline DxGlobal dx;
	inline IDirect3DDevice9* device = reinterpret_cast<IDirect3DDevice9*>(shaderapidx9 + 0xA6050);

}

#endif // ! cgoffsets
