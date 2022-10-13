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
r::box_s::box_s(vec3_t const origin, vec3_t const mins, vec3_t const maxs)
{
	//box_s box{};

	vec3_t lowA, lowB, lowC, lowD;
	vec3_t highA, highB, highC, highD;

	lowA[0] = origin[0] - mins[0];
	lowA[1] = origin[1] - mins[1];
	lowA[2] = origin[2] - mins[2];

	lowB[0] = origin[0] + mins[0];
	lowB[1] = origin[1] + mins[1];
	lowB[2] = origin[2] - mins[2];

	lowC[0] = origin[0] - mins[0];
	lowC[1] = origin[1] + mins[1];
	lowC[2] = origin[2] - mins[2];

	lowD[0] = origin[0] + mins[0];
	lowD[1] = origin[1] - mins[1];
	lowD[2] = origin[2] - mins[2];

	highA[0] = lowA[0];
	highA[1] = lowA[1];
	highA[2] = origin[2] + maxs[2];

	highB[0] = lowB[0];
	highB[1] = lowB[1];
	highB[2] = origin[2] + maxs[2];

	highC[0] = lowC[0];
	highC[1] = lowC[1];
	highC[2] = origin[2] + maxs[2];

	highD[0] = lowD[0];
	highD[1] = lowD[1];
	highD[2] = origin[2] + maxs[2];

	this->lowA_valid = R_WorldToScreen(lowA, this->lowA);
	this->lowB_valid = R_WorldToScreen(lowB, this->lowB);
	this->lowC_valid = R_WorldToScreen(lowC, this->lowC);
	this->lowD_valid = R_WorldToScreen(lowD, this->lowD);

	this->highA_valid = R_WorldToScreen(highA, this->highA);
	this->highB_valid = R_WorldToScreen(highB, this->highB);
	this->highC_valid = R_WorldToScreen(highC, this->highC);
	this->highD_valid = R_WorldToScreen(highD, this->highD);

	//return box;
}
void r::box_s::R_DrawConstructedBoxEdges(vec4_t col) const
{
	if (!ImGui::GetCurrentContext())
		return;

	if (this->lowA_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->lowC[0], this->lowC[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowB_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->lowD[0], this->lowD[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowC_valid && this->lowB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowC[0], this->lowC[1]), ImVec2(this->lowB[0], this->lowB[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowD_valid && this->lowA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowD[0], this->lowD[1]), ImVec2(this->lowA[0], this->lowA[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highA_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highA[0], this->highA[1]), ImVec2(this->highC[0], this->highC[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highB[0], this->highB[1]), ImVec2(this->highD[0], this->highD[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highC_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highC[0], this->highC[1]), ImVec2(this->highB[0], this->highB[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->highD_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->highD[0], this->highD[1]), ImVec2(this->highA[0], this->highA[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowA_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->highA[0], this->highA[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowB_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->highB[0], this->highB[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowC_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowC[0], this->lowC[1]), ImVec2(this->highC[0], this->highC[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);

	if (this->lowD_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(this->lowD[0], this->lowD[1]), ImVec2(this->highD[0], this->highD[1]), IM_COL32(col[0], col[1], col[2], col[3]), 1.f);
}
void r::box_s::R_DrawConstructedBox(vec4_t col) const
{
	if (!ImGui::GetCurrentContext())
		return;

	if (this->lowA_valid && this->highC_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->highC[0], this->highC[1]), ImVec2(this->lowC[0], this->lowC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowA_valid && this->highA_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA[0], this->highA[1]), ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->highC[0], this->highC[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowB_valid && this->highD_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->highD[0], this->highD[1]), ImVec2(this->lowD[0], this->lowD[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowB_valid && this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highB[0], this->highB[1]), ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->highD[0], this->highD[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowC_valid && this->highB_valid && this->lowB_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowC[0], this->lowC[1]), ImVec2(this->highB[0], this->highB[1]), ImVec2(this->lowB[0], this->lowB[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowC_valid && this->highC_valid && this->highB_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highC[0], this->highC[1]), ImVec2(this->lowC[0], this->lowC[1]), ImVec2(this->highB[0], this->highB[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowD_valid && this->highA_valid && this->lowA_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowD[0], this->lowD[1]), ImVec2(this->highA[0], this->highA[1]), ImVec2(this->lowA[0], this->lowA[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowD_valid && this->highD_valid && this->highA_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highD[0], this->highD[1]), ImVec2(this->lowD[0], this->lowD[1]), ImVec2(this->highA[0], this->highA[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->highA_valid && this->highB_valid && this->highC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA[0], this->highA[1]), ImVec2(this->highB[0], this->highB[1]), ImVec2(this->highC[0], this->highC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->highA_valid && this->highB_valid && this->highD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->highA[0], this->highA[1]), ImVec2(this->highB[0], this->highB[1]), ImVec2(this->highD[0], this->highD[1]), IM_COL32(col[0], col[1], col[2], col[3]));

	if (this->lowA_valid && this->lowB_valid && this->lowC_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->lowC[0], this->lowC[1]), IM_COL32(col[0], col[1], col[2], col[3]));
	if (this->lowA_valid && this->lowB_valid && this->lowD_valid)
		ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(this->lowA[0], this->lowA[1]), ImVec2(this->lowB[0], this->lowB[1]), ImVec2(this->lowD[0], this->lowD[1]), IM_COL32(col[0], col[1], col[2], col[3]));
}