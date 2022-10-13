#pragma once
#include "pch.h"

bool r::R_WorldToScreen(vec3_t origin, vec2_t screen)
{
	//const matrix3x4_t& matrix = (matrix3x4_t)view_matrix;
	screen[0] = cg::viewMatrix->viewMatrix[0][0] * origin[0] +cg::viewMatrix->viewMatrix[0][1] * origin[1] +cg::viewMatrix->viewMatrix[0][2] * origin[2] + cg::viewMatrix->viewMatrix[0][3];
	screen[1] = cg::viewMatrix->viewMatrix[1][0] * origin[0] +cg::viewMatrix->viewMatrix[1][1] * origin[1] +cg::viewMatrix->viewMatrix[1][2] * origin[2] + cg::viewMatrix->viewMatrix[1][3];

	float w = cg::viewMatrix->viewMatrix[3][0] * origin[0] +cg::viewMatrix->viewMatrix[3][1] * origin[1] +cg::viewMatrix->viewMatrix[3][2] * origin[2] + cg::viewMatrix->viewMatrix[3][3];

	if (w < 0.01f)
	{
		return false;
	}

	float invw = 1.0f / w;
	screen[0] *= invw;
	screen[1] *= invw;

	//RECT rect;
	//vec2_t res;

	//window = FindWindowA(NULL, D3D::glob::windowName);
	//D3D::GetWindowDimensions(window, &rect);
	//D3D::Get3DViewResolution(rect, res);



	float x, y, dispX, dispY;
	//x = D3D::CenterX(rect);
	//y = D3D::CenterY(rect);

	dispX = ImGui::GetIO().DisplaySize[0];
	dispY = ImGui::GetIO().DisplaySize[1];

	x = dispX / 2;
	y = dispY / 2;

	x += 0.5f * screen[0] * dispX + 0.5f;
	y -= 0.5f * screen[1] * dispY + 0.5f;

	screen[0] = x;
	screen[1] = y;

	return true;
}