#pragma once

#ifndef rmenu
#define rmenu
#include "pch.h"

namespace r
{

	bool R_OpenMenu(IDirect3DDevice9* pDevice);
	void R_EndRender();
	void R_MenuStyle(float transparencyScale = 1.f);
}

#endif