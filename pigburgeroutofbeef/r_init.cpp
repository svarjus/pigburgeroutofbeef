#include "pch.h"


bool r::R_Init()
{

	cg::dx.device = *(IDirect3DDevice9**)(cg::shaderapidx9 + 0xA6050);
	cg::dx.d3d9 = *(IDirect3D9**)(cg::shaderapidx9 + 0x8A60C);

	if (!cg::dx.device) {
		fs::Log_Write(LOG_ERROR, "R_Init(): dx->device is invalid\n");
		return false;
	}

	PVOID* vTable = *reinterpret_cast<PVOID**>(cg::dx.device);
	hook* a = nullptr;
	pEndScene = (endScene)vTable[42];


	if (a->install(&(PVOID&)pEndScene, draw_func) != S_OK) {
		fs::Log_Write(LOG_ERROR, "R_Init(): a->install(&(PVOID&)pEndScene, draw_func) != S_OK\n");
		return false;
	}

	return true;

}
bool r::R_ImGui(IDirect3DDevice9* pDevice)
{
	if (ImGui::GetCurrentContext())
		return true;

	fs::Log_Write(LOG_NONE, "Writing ImGui context\n");

	ImGui::CreateContext();

	ImGuiIO* io = &ImGui::GetIO();

	io->WantCaptureKeyboard = true;
	io->WantCaptureMouse = true;
	io->MouseDrawCursor = true;

	const char* const window_name = "Counter-Strike: Global Offensive - Direct3D 9";
	void* hwnd = FindWindowA(NULL, window_name);
	oWndProc = (WNDPROC)SetWindowLongPtr((HWND)hwnd, GWL_WNDPROC, (LONG_PTR)WndProc);

	if (!hwnd) {
		fs::Log_Write(LOG_FATAL, "Invalid hwnd (%s) handle\n", window_name);
		return false;
	}

	if (!ImGui_ImplWin32_Init(hwnd)) {
		fs::Log_Write(LOG_FATAL, "ImGui_ImplWin32_Init(%s) returned false\n", window_name);
		return false;
	}

	if (!ImGui_ImplDX9_Init(pDevice)) {
		fs::Log_Write(LOG_FATAL, "ImGui_ImplDX9_Init() returned false.. possibly nullptr dx->device\n");
		return false;
	}
	return true;
}