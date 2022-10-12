#include "pch.h"

LRESULT CALLBACK r::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if(ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return 1l;
	

	switch (uMsg) {
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		ImGui_ImplDX9_InvalidateDeviceObjects();
		break;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	
}

HRESULT __stdcall r::draw_func(IDirect3DDevice9* pDevice)
{
	if (!R_ImGui(pDevice)) {
		fs::Log_Write(LOG_FATAL, "R_ImGui returned false\n");
	}
	const ImGuiIO* io = &ImGui::GetIO();
	if (R_OpenMenu(pDevice)) {

		if (io->KeysDownDuration['F'] == 0.0f)
			ui.should_draw_menu = !ui.should_draw_menu;

		if (io->KeysDownDuration[VK_HOME] == 0.0f) {
			std::cout << "enginetrace exists at: 0x" << std::hex << interfaces::engineTrace << '\n';
			vec3_t a = { 1,1,1 };

			Ray_t ray(vec3_t{ -5000,-5000,-1000 }, vec3_t{ 5000,5000,1000 }, vec3_t{-1,-1,-1}, vec3_t{1,1,1});
			CTraceFilter filter;
			filter.pSkip = 0;
			trace_t trace;

			interfaces::engineTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &trace);

			for (int i = 0; i < 3; i++)
				std::cout << "end[" << i << "]: " << trace.endpos[i] << '\n';

			
		}


		R_EndRender();
	}

	return pEndScene(pDevice);
}