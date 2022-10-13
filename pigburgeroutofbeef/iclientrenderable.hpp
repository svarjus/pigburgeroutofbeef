#pragma once

#ifndef iclientrenderable
#define iclientrenderable

#include "pch.h"

struct Vector;
typedef unsigned short ClientShadowHandle_t;


//-----------------------------------------------------------------------------
// Information needed to draw a model
//-----------------------------------------------------------------------------
struct RenderableInstance_t
{
	uint8_t m_nAlpha;
};
//-----------------------------------------------------------------------------
// Handle to an renderable in the client leaf system
//-----------------------------------------------------------------------------
typedef unsigned short ClientRenderHandle_t;

enum
{
	INVALID_CLIENT_RENDER_HANDLE = (ClientRenderHandle_t)0xffff,
};

//-----------------------------------------------------------------------------
// Purpose: All client entities must implement this interface.
//-----------------------------------------------------------------------------
class IClientRenderable
{
public:
	// Gets at the containing class...
	virtual void* GetIClientUnknown() = 0;

	// Data accessors
	virtual vec_t* GetRenderOrigin(void) = 0;
	virtual vec_t* const& GetRenderAngles(void) = 0;
	virtual bool					ShouldDraw(void) = 0;
	virtual int					    GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
	virtual void					Unused(void) const {}

	virtual ClientShadowHandle_t	GetShadowHandle() const = 0;

	// Used by the leaf system to store its render handle.
	virtual ClientRenderHandle_t& RenderHandle() = 0;

	// Render baby!
	virtual const model_t* GetModel() const = 0;
	virtual int						DrawModel(int flags, const RenderableInstance_t& instance) = 0;

	// Get the body parameter
	virtual int		GetBody() = 0;

	// Determine the color modulation amount
	virtual void	GetColorModulation(float* color) = 0;

	// Returns false if the entity shouldn't be drawn due to LOD. 
	// (NOTE: This is no longer used/supported, but kept in the vtable for backwards compat)
	virtual bool	LODTest() = 0;

	// Call this to get the current bone transforms for the model.
	// currentTime parameter will affect interpolation
	// nMaxBones specifies how many matrices pBoneToWorldOut can hold. (Should be greater than or
	// equal to studiohdr_t::numbones. Use MAXSTUDIOBONES to be safe.)
	virtual bool	SetupBones(Matrix3x4* pBoneToWorldOut3x4, int nMaxBones, int boneMask, float currentTime) = 0; //[3][4]
};

#endif