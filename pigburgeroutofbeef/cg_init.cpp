#include "pch.h"

void cg::CG_GetModules()
{
	shaderapidx9 = (DWORD)GetModuleHandle("shaderapidx9.dll");

}
void cg::CG_Init()
{
	CG_GetModules();

	r::R_Init();
}