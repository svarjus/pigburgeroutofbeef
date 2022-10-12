#include "pch.h"


bool r::R_Init()
{
	if (!cg::dx->device) {
		fs::Log_Write(LOG_ERROR, "R_Init(): dx->device is invalid\n");
		return false;
	}

	PVOID* vTable = *reinterpret_cast<PVOID**>(cg::dx->device);

	hook* a = nullptr;

	pEndScene = (endScene)vTable[42];

	if (pEndScene)
		fs::Log_Write(LOG_NONE, "endscene (0x%p)\n", pEndScene);

	//if (a->install(&(PVOID&)pEndScene, draw_func) != S_OK) {
	//	fs::Log_Write(LOG_ERROR, "R_Init(): a->install(&(PVOID&)pEndScene, draw_func) != S_OK\n");
	//	return false;
	//}

	return true;

}