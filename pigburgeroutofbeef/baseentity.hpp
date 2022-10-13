#pragma once

#ifndef _baseentity
#define _baseentity

#include "pch.h"

inline int InternalCheckDeclareClass(const char* pClassName, const char* pClassNameMatch, void* pTestPtr, void* pBasePtr)
{
	// This makes sure that casting from ThisClass to BaseClass works right. You'll get a compiler error if it doesn't
	// work at all, and you'll get a runtime error if you use multiple inheritance.
	//Assert(pTestPtr == pBasePtr);

	// This is triggered by IMPLEMENT_SERVER_CLASS. It does DLLClassName::CheckDeclareClass( #DLLClassName ).
	// If they didn't do a DECLARE_CLASS in DLLClassName, then it'll be calling its base class's version
	// and the class names won't match.
	//Assert((void*)pClassName == (void*)pClassNameMatch);
	return 0;
}


#define DECLARE_CLASS_NOBASE( className ) \
		typedef className ThisClass; \
		template <typename T> friend int CheckDeclareClass_Access(T *, const char *pShouldBe); \
		static int CheckDeclareClass( const char *pShouldBe ) \
		{ \
			return InternalCheckDeclareClass( pShouldBe, #className, 0, 0 ); \
		} 

// If you do a DECLARE_SERVERCLASS, you need to do this inside the class definition.
#define DECLARE_SERVERCLASS()									\
	public:														\
		virtual void* GetServerClass();					\
		static void *m_pClassSendTable;					\
		template <typename T> friend int ServerClassInit(T *);	\
		virtual int YouForgotToImplementOrDeclareServerClass();	\

#define DECLARE_SERVERCLASS_NOBASE()							\
	public:														\
		template <typename T> friend int ServerClassInit(T *);	\

#define DECLARE_PREDICTABLE()	

typedef char datamap_t[28];

#define DECLARE_SIMPLE_DATADESC() \
	static datamap_t m_DataMap; \
	static datamap_t *GetBaseMap(); \
	template <typename T> friend void DataMapAccess(T *, void **p); \
	template <typename T> friend void *DataMapInit(T *);


#define	DECLARE_DATADESC() \
	DECLARE_SIMPLE_DATADESC() \
	virtual void *GetDataDescMap( void );

#define ALLOW_SCRIPT_ACCESS() 																template <typename T> friend void *GetScriptDesc(T *);
#define DECLARE_ENT_SCRIPTDESC()													ALLOW_SCRIPT_ACCESS(); virtual void *GetScriptDesc()

class CBaseHandle;

class CBaseEntity : public IServerEntity
{
public:

	DECLARE_CLASS_NOBASE(CBaseEntity);

	//----------------------------------------
	// Class vars and functions
	//----------------------------------------
	static inline void Debug_Pause(bool bPause);
	static inline bool Debug_IsPaused(void);
	static inline void Debug_SetSteps(int nSteps);
	static inline bool Debug_ShouldStep(void);
	static inline bool Debug_Step(void);

	static bool				m_bInDebugSelect;
	static int				m_nDebugPlayer;

protected:

	static bool				m_bDebugPause;		// Whether entity i/o is paused for debugging.
	static int				m_nDebugSteps;		// Number of entity outputs to fire before pausing again.

	static bool				sm_bDisableTouchFuncs;	// Disables PhysicsTouch and PhysicsStartTouch function calls
public:
	static bool				sm_bAccurateTriggerBboxChecks;	// SOLID_BBOX entities do a fully accurate trigger vs bbox check when this is set

public:
	// If bServerOnly is true, then the ent never goes to the client. This is used
	// by logical entities.
	CBaseEntity(bool bServerOnly = false);
	virtual ~CBaseEntity();

	// Entities are not copyable
	CBaseEntity(const CBaseEntity&) = delete;
	CBaseEntity& operator=(const CBaseEntity&) = delete;

	// prediction system
	DECLARE_PREDICTABLE();
	// network data
	DECLARE_SERVERCLASS();
	// data description
	DECLARE_DATADESC();


	// memory handling
	void* operator new(size_t stAllocateBlock);
	void* operator new(size_t stAllocateBlock, int nBlockUse, const char* pFileName, int nLine);
	void operator delete(void* pMem);
	void operator delete(void* pMem, int nBlockUse, const char* pFileName, int nLine) { operator delete(pMem); }

	// Class factory
	static CBaseEntity* CreatePredictedEntityByName(const char* classname, const char* module, int line, bool persist = false);

	// IHandleEntity overrides.
public:
	virtual void			SetRefEHandle(const CBaseHandle& handle);
	virtual const			CBaseHandle& GetRefEHandle() const;

	// IServerUnknown overrides
	virtual ICollideable* GetCollideable();
	virtual void* GetNetworkable();
	virtual CBaseEntity* GetBaseEntity();

	// IServerEntity overrides.
public:
	virtual void			SetModelIndex(int index);
	virtual int				GetModelIndex(void) const;
	virtual const char* GetModelName(void) const;
	const char* ScriptGetModelName(void) const;

	virtual const char*		GetAIAddOn(void) const;

public:
	// virtual methods for derived classes to override
	virtual bool			TestCollision(const Ray_t& ray, unsigned int mask, trace_t& trace);
	virtual	bool			TestHitboxes(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr);
	virtual void			ComputeWorldSpaceSurroundingBox(vec3_t pWorldMins, vec3_t pWorldMaxs);

public:
	// An inline version the game code can use
	void* CollisionProp();
	const void* CollisionProp() const;
	void* NetworkProp();
	const void* NetworkProp() const;

	bool					IsCurrentlyTouching(void) const;
	const vec_t* GetAbsOrigin(void) const;
	const vec_t GetAbsAngles(void) const;  // see also GetVectors()
	inline vec_t*			Forward() const __restrict; ///< get my forward (+x) vector
	inline vec_t* Left() const __restrict;    ///< get my left    (+y) vector
	inline vec_t* Up() const __restrict;      ///< get my up      (+z) vector


};

#endif