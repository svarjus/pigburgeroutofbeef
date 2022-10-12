#include "pch.h"

Ray_t::Ray_t(vec3_t const start, vec3_t const end)
{
	//Assert(&end);
	VectorSubtract(end, start, m_Delta);

	m_IsSwept = (m_Delta[0] || m_Delta[1] || m_Delta[2]);

	VectorClear(m_Extents);
	m_IsRay = true;

	// Offset m_Start to be in the center of the box...
	VectorClear(m_StartOffset);
	VectorCopy(start, m_Start);
}
Ray_t::Ray_t(vec3_t const start, vec3_t const end, vec3_t const mins, vec3_t const maxs)
{
	//Assert(&end);
	VectorSubtract(end, start, m_Delta);

	m_IsSwept = (m_Delta[0] || m_Delta[1] || m_Delta[2]);

	VectorSubtract(maxs, mins, m_Extents);
	for (int i = 0; i < 3; i++)
		m_Extents[i] *= 0.5f;

	m_IsRay = ((m_Delta[0] * m_Delta[0] + m_Delta[1] * m_Delta[1] + m_Delta[2] * m_Delta[2]) < 1e-6);

	// Offset m_Start to be in the center of the box...
	VectorAdd(mins, maxs, m_StartOffset);

	for (int i = 0; i < 3; i++)
		m_StartOffset[i] *= 0.5f;
	VectorAdd(start, m_StartOffset, m_Start);

	for (int i = 0; i < 3; i++)
		m_StartOffset[i] *= -1.0f;
}