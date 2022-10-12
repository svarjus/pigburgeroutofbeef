#pragma once

#ifndef ENGINE_ICOLLIDEABLE_H
#define ENGINE_ICOLLIDEABLE_H

#include "pch.h"

enum SolidType_t
{
	SOLID_NONE = 0,	// no solid model
	SOLID_BSP = 1,	// a BSP tree
	SOLID_BBOX = 2,	// an AABB
	SOLID_OBB = 3,	// an OBB (not implemented yet)
	SOLID_OBB_YAW = 4,	// an OBB, constrained so that it can only yaw
	SOLID_CUSTOM = 5,	// Always call into the entity for tests
	SOLID_VPHYSICS = 6,	// solid vphysics object, get vcollide from the model and collide with that
	SOLID_LAST,
};

struct trace_t;

struct ICollideable
{
	// Gets at the entity handle associated with the collideable
	virtual IHandleEntity* GetEntityHandle() = 0;

	// These methods return the bounds of an OBB measured in "collision" space
	// which can be retreived through the CollisionToWorldTransform or
	// GetCollisionOrigin/GetCollisionAngles methods
	virtual const vec_t* OBBMins() const = 0;
	virtual const vec_t* OBBMaxs() const = 0;

	// Returns the bounds of a world-space box used when the collideable is being traced
	// against as a trigger. It's only valid to call these methods if the solid flags
	// have the FSOLID_USE_TRIGGER_BOUNDS flag set.
	virtual void			WorldSpaceTriggerBounds(vec3_t pVecWorldMins, vec3_t pVecWorldMaxs) const = 0;

	// custom collision test
	virtual bool			TestCollision(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr) = 0;

	// Perform hitbox test, returns true *if hitboxes were tested at all*!!
	virtual bool			TestHitboxes(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr) = 0;

	// Returns the BRUSH model index if this is a brush model. Otherwise, returns -1.
	virtual int				GetCollisionModelIndex() = 0;

	// Return the model, if it's a studio model.
	virtual const void* GetCollisionModel() = 0;

	// Get angles and origin.
	virtual const vec_t* GetCollisionOrigin() const = 0;
	virtual const vec_t* GetCollisionAngles() const = 0;
	virtual const vec_t* CollisionToWorldTransform() const = 0; //returns array[3][4]


	// Return a SOLID_ define.
	virtual SolidType_t		GetSolid() const = 0;
	virtual int				GetSolidFlags() const = 0;

	// Gets at the containing class...
	virtual void* GetIClientUnknown() = 0;

	// We can filter out collisions based on collision group
	virtual int				GetCollisionGroup() const = 0;

	// Returns a world-aligned box guaranteed to surround *everything* in the collision representation
	// Note that this will surround hitboxes, trigger bounds, physics.
	// It may or may not be a tight-fitting box and its volume may suddenly change
	virtual void			WorldSpaceSurroundingBounds(vec3_t pVecMins, vec3_t pVecMaxs) = 0;

	virtual uint32_t			GetRequiredTriggerFlags() const = 0;

	// returns NULL unless this collideable has specified FSOLID_ROOT_PARENT_ALIGNED
	virtual const vec_t* GetRootParentToWorldTransform() const = 0; //returns array[3][4]
	virtual void* GetVPhysicsObject() const = 0; //IPhysicsObject

};

#endif