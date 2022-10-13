#pragma once

#ifndef modelprivate
#define modelprivate

#include "pch.h"


//-----------------------------------------------------------------------------
// Reference to a loaded studiomdl 
//-----------------------------------------------------------------------------
typedef unsigned short MDLHandle_t;

typedef void* FileNameHandle_t;
enum modtype_t
{
	mod_bad = 0,
	mod_brush,
	mod_sprite,
	mod_studio
};
struct spritedata_t
{
	int				numframes;
	int				width;
	int				height;
	void* sprite;
};

struct model_t
{
	FileNameHandle_t	fnHandle;
	char				szPathName[260];

	int					nLoadFlags;		// mark loaded/not loaded
	int					nServerCount;	// marked at load

	modtype_t			type;
	int					flags;			// MODELFLAG_???

	// volume occupied by the model graphics	
	vec3_t				mins, maxs;
	float				radius;
	void* m_pKeyValues;

	char brush[24];



};


#endif