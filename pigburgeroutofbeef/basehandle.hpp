
#ifndef BASEHANDLE_H
#define BASEHANDLE_H
#ifdef _WIN32
#pragma once
#endif

#include "pch.h"

enum INVALID_EHANDLE_tag
{
	INVALID_EHANDLE
};

class CBaseHandle
{
	friend class CBaseEntityList;

public:

	CBaseHandle();
	CBaseHandle(INVALID_EHANDLE_tag);
	CBaseHandle(const CBaseHandle& other);
	explicit CBaseHandle(IHandleEntity* pHandleObj);
	CBaseHandle(int iEntry, int iSerialNumber);

	// NOTE: The following constructor is not type-safe, and can allow creating an
	//       arbitrary CBaseHandle that doesn't necessarily point to an actual object.
	//
	// It is your responsibility to ensure that the target of the handle actually points
	// to the object you think it does.  Generally, the argument to this function should
	// have been obtained from CBaseHandle::ToInt() on a valid handle.
	static CBaseHandle UnsafeFromIndex(int index);

	void Init(int iEntry, int iSerialNumber);
	void Term();

	// Even if this returns true, Get() still can return return a non-null value.
	// This just tells if the handle has been initted with any values.
	bool IsValid() const;

	int GetEntryIndex() const;
	int GetSerialNumber() const;

	int ToInt() const;
	bool operator !=(const CBaseHandle& other) const;
	bool operator ==(const CBaseHandle& other) const;
	bool operator ==(const IHandleEntity* pEnt) const;
	bool operator !=(const IHandleEntity* pEnt) const;
	bool operator <(const CBaseHandle& other) const;
	bool operator <(const IHandleEntity* pEnt) const;

	// Assign a value to the handle.
	const CBaseHandle& operator=(const IHandleEntity* pEntity);
	const CBaseHandle& Set(const IHandleEntity* pEntity);

	// Use this to dereference the handle.
	// Note: this is implemented in game code (ehandle.h)
	IHandleEntity* Get() const;


protected:
	// The low NUM_SERIAL_BITS hold the index. If this value is less than MAX_EDICTS, then the entity is networkable.
	// The high NUM_SERIAL_NUM_BITS bits are the serial number.
	uint32	m_Index;
};

#endif