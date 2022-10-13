#pragma once

#ifndef cglocal
#define cglocal

#include "pch.h"

namespace cg
{
	struct vmatrix
	{
		float viewMatrix[4][4];
	};

	struct DxGlobal
	{
		
		IDirect3D9* d3d9;
		IDirect3DDevice9* device;

	};

	struct GlobalVars {
		float realtime;
		int framecount;
		float absoluteFrameTime;
		float absoluteFrameStartTimestddev;
		float currenttime;
		float frametime;
		int maxClients;
		int tickCount;
		float intervalPerTick;
	};

}


#endif