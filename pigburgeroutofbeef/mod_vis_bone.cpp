#include "pch.h"


void r::Mod_DrawBones(IClientEntity* cent, int points[2])
{
	if (!cent)
		return;

	vec3_t bonepos, nextbone;
	vec2_t b_xy, e_xy;

	cent->GetBone(points[0], bonepos);
	cent->GetBone(points[1], nextbone);


	if (R_WorldToScreen(bonepos, b_xy) && R_WorldToScreen(nextbone, e_xy)) {
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(b_xy[0], b_xy[1]), ImVec2(e_xy[0], e_xy[1]), IM_COL32(255, 255, 255, 255), 3.f);

	}

}