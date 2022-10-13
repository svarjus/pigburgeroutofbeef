#include "pch.h"



const int& IClientEntity::GetHealth()
{
	return *(int*)((uintptr_t)this + cg::m_iHealth);
}
void IClientEntity::GetOrigin(vec3_t out)
{
	out[0] = *(float*)((uintptr_t)this + cg::m_vecOrigin);
	out[1] = *(float*)((uintptr_t)this + cg::m_vecOrigin + 4);
	out[2] = *(float*)((uintptr_t)this + cg::m_vecOrigin + 8);


}
void IClientEntity::GetAngles(vec3_t out)
{
	out[0] = *(float*)((uintptr_t)this + cg::dwClientState_ViewAngles);
	out[1] = *(float*)((uintptr_t)this + cg::dwClientState_ViewAngles + 4);
	out[2] = *(float*)((uintptr_t)this + cg::dwClientState_ViewAngles + 8);
}
const int& IClientEntity::GetCurrentWeapon()
{
	return *(int*)((uintptr_t)this + cg::m_hActiveWeapon);

}