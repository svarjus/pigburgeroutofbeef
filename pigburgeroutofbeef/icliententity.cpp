#include "pch.h"



const int& IClientEntity::GetHealth()
{
	return *(int*)((uintptr_t)this + cg::m_iHealth);
}
const bool IClientEntity::isAlive()
{
	return this->GetHealth() > 0;
}
const int& IClientEntity::TeamNumber()
{
	return *(int*)((uintptr_t)this + cg::m_iTeamNum);

}
const bool IClientEntity::InMyTeam()
{
	return *(int*)((uintptr_t)this + cg::m_iTeamNum) == *(int*)((uintptr_t)(interfaces::entityList->GetClientEntity(interfaces::local->GetLocalPlayer())) + cg::m_iTeamNum);
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
void IClientEntity::GetBoneMatrix( Matrix3x4* out)
{
	uintptr_t boneMtx = ((uintptr_t)this + cg::m_dwBoneMatrix);

	/*boneMtx += (sizeof(Matrix3x4) * index);*/

	//std::cout << "m_dwBoneMatrix: 0x" << std::hex << boneMtx << '\n';

	//Matrix3x4 mtx{};
	//GetBoneMatrix(boneMtx, &mtx);

	out = reinterpret_cast<Matrix3x4*>(boneMtx);



}
void IClientEntity::GetBone(int16_t index, vec3_t position)
{

	static Matrix3x4 mtx[257];
	this->SetupBones(mtx, 256, 0, cg::globalVars->currenttime);
	mtx[index].origin(position);

}