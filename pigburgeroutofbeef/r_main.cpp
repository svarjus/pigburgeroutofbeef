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
			system("cls");
			std::cout << "interfaces::local exists at: 0x" << std::hex << interfaces::local << '\n';
			//vec3_t a = { 1,1,1 };

			//Ray_t ray(vec3_t{ -5000,-5000,-1000 }, vec3_t{ 5000,5000,1000 }, vec3_t{-1,-1,-1}, vec3_t{1,1,1});
			//CTraceFilter filter;
			//filter.pSkip = 0;
			//trace_t trace;

			//interfaces::engineTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &trace);

			//for (int i = 0; i < 3; i++)
			//	std::cout << "end[" << i << "]: " << trace.endpos[i] << '\n';
			
		}
		if (interfaces::local->IsInGame()) {
			for (int i = 0; i < interfaces::local->GetMaxClients(); i++) {
				const auto a = interfaces::entityList->GetClientEntity(i);
				
				if(!a)
					continue;

				int health = a->GetHealth();
				vec3_t org;
				a->GetOrigin(org);
				vec2_t xy{ 0,0 };
				if (R_WorldToScreen(org, xy)) {
					char buffer[25];
					sprintf_s(buffer, "health: %i", health);

					if (io->KeysDownDuration[VK_END] == 0.f) {
						Matrix3x4 mtx[257]{};
						a->SetupBones(mtx, 257, 0, cg::globalVars->currenttime);
					}

					ImGui::GetBackgroundDrawList()->AddText(ImVec2(xy[0], xy[1]), IM_COL32(255, 255, 0, 255), buffer);
				}
				
			}
		}


		R_EndRender();
	}

	return pEndScene(pDevice);
}