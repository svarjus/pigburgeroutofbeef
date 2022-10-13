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
				IClientEntity* a = interfaces::entityList->GetClientEntity(i);
				
				if(!a || i == interfaces::local->GetLocalPlayer())
					continue;

				if (!a->isAlive())
					continue;


				IClientEntity* self = interfaces::entityList->GetClientEntity(interfaces::local->GetLocalPlayer());


				vec3_t org, head, selfOrg;
				a->GetOrigin(org);
				self->GetOrigin(selfOrg);

				a->GetBone(8, head);
				vec2_t xy{ 0,0 };

				if (R_WorldToScreen(head, xy)) {
					int health = a->GetHealth();
					char buffer[25];
					sprintf_s(buffer, "%i", health);
					const model_t* model = a->GetModel();
					const bool myTeam = a->InMyTeam();

					if (model) {

						//if (glm::distance(glm::vec3(model->mins[0], model->mins[1], model->mins[2]), glm::vec3(model->maxs[0], model->maxs[1], model->maxs[2])) > 150) //what is u!!!!
						//	continue;


						//r::box_s box(org, model->mins, model->maxs);
						//vec4_t col;
						//col[0] = myTeam == true ? 0 : 255;
						//col[1] = myTeam == true ? 255 : 0;
						//col[2] = 0;
						//col[3] = 255;

						//box.R_DrawConstructedBoxEdges(col);
						//col[3] = 55;
						//box.R_DrawConstructedBox(col);



					}
					//std::cout << mtx[8][0][3] << '\n';
					vec3_t curbone;
					for (int i = 0; i < 30; i++) {
						a->GetBone(i, curbone);
						vec2_t _xy;

						//if (R_WorldToScreen(curbone, _xy)) {
						//	ImGui::GetBackgroundDrawList()->AddText(ImVec2(_xy[0], _xy[1]), myTeam == true ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255), std::to_string(i).c_str());

						//}
						int points[2] = { i, i+1 };
						Mod_DrawBones(a, points);
					}

					ImGui::GetBackgroundDrawList()->AddText(ImVec2(xy[0], xy[1]), myTeam == true ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255), buffer);
				}
				
			}
		}


		R_EndRender();
	}

	return pEndScene(pDevice);
}