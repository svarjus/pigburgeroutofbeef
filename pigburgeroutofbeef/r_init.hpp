#pragma once

#ifndef rinit
#define rinit

#include "pch.h"

namespace r
{
	bool R_Init();
	HRESULT __stdcall draw_func(IDirect3DDevice9* pDevice);

	typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
	inline endScene pEndScene;

	
}

#endif