#pragma once

#ifndef drawtools
#define drawtools

#include "pch.h"

namespace r
{
	bool R_WorldToScreen(vec3_t origin, vec2_t screen);

	struct box_s
	{
		box_s(const vec3_t origin, const vec3_t mins, const vec3_t maxs);

		void R_DrawConstructedBox(vec4_t col) const;
		void R_DrawConstructedBoxEdges(vec4_t col) const;

	private:

		vec2_t lowA;
		vec2_t lowB;
		vec2_t lowC;
		vec2_t lowD;

		vec2_t highA;
		vec2_t highB;
		vec2_t highC;
		vec2_t highD;

		bool lowA_valid;
		bool lowB_valid;
		bool lowC_valid;
		bool lowD_valid;

		bool highA_valid;
		bool highB_valid;
		bool highC_valid;
		bool highD_valid;

	};
}


#endif