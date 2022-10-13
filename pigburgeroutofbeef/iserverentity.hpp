#pragma once

#ifndef ISERVERENTITY_H
#define ISERVERENTITY_H
#ifdef _WIN32
#pragma once
#endif

#include "pch.h"

//class SINGLE_INHERITANCE CBaseEntity;
class CBaseHandle;
class CBaseEntity;
//// An IHandleEntity-derived class can go into an entity list and use ehandles.
//class IHandleEntity
//{
//public:
//	virtual ~IHandleEntity() {}
//	virtual void SetRefEHandle(const CBaseHandle& handle) = 0;
//	virtual const CBaseHandle& GetRefEHandle() const = 0;
//#ifdef _GAMECONSOLE
//	IHandleEntity() :
//		m_bIsStaticProp(false)
//	{
//	}
//
//	bool m_bIsStaticProp;
//#endif
//};


// This is the server's version of IUnknown. We may want to use a QueryInterface-like
// mechanism if this gets big.
class IServerUnknown : public IHandleEntity
{
public:
	// Gets the interface to the collideable + networkable representation of the entity
	virtual ICollideable* GetCollideable() = 0;
	virtual void* GetNetworkable() = 0;
	virtual CBaseEntity* GetBaseEntity() = 0;
};

class IServerEntity : public IServerUnknown
{
public:
	virtual					~IServerEntity() {}

	// Previously in pev
	virtual int				GetModelIndex(void) const = 0;
	virtual const char*		GetModelName(void) const = 0;

	virtual void			SetModelIndex(int index) = 0;
};


#endif