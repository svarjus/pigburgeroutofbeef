#pragma once

#ifndef rinit
#define rinit

#include "pch.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace r
{
	struct ui_t
	{
		bool should_draw_menu;

	}; inline ui_t ui;

	bool R_Init();
	bool R_ImGui(IDirect3DDevice9* pDevice);

	HRESULT __stdcall draw_func(IDirect3DDevice9* pDevice);
	inline WNDPROC oWndProc; extern LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice); inline endScene pEndScene;



	
}

#endif