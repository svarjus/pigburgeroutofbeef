// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define ANGLE2SHORT( x )  ( (int)( ( x ) * 65536 / 360 ) & 65535 )
#define SHORT2ANGLE( x )  ( ( x ) * ( 360.0 / 65536 ) )

#define	PITCH					0		// up / down
#define	YAW						1		// left / right
#define	ROLL					2		// fall over


typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#define PI 3.14159265f
#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorAddAll(a,b,c)		((c)[0]=(a)[0]+(b),(c)[1]=(a)[1]+(b),(c)[2]=(a)[2]+(b))
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define VectorScaleAll(a,b,c)	((c)[0]=(a)[0]*(b),(c)[1]=(a)[1]*(b),(c)[2]=(a)[2]*(b))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorClear( a )              ( ( a )[0] = ( a )[1] = ( a )[2] = 0 )

#define DEG2RAD(a) (((a) * M_PI) / 180.0F)
#define RAD2DEG(a) (((a) * 180.0f) / M_PI)
#define RAD2SHORT(a) ((a) * (32768.f / (float)M_PI))
#define SHORT2RAD(a) ((a) * ((float)M_PI / 32768.f))
#define SHORT2DEG(a) (((a) / 32768.f) * 180.0f)

// plane types are used to speed some tests
// 0-2 are axial planes
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2
#define	PLANE_NON_AXIAL	3

#pragma warning(disable : 26495)

// add headers that you want to pre-compile here
#include "framework.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <psapi.h>
#include <iostream>
#include <utility>
#include <filesystem>
#include <direct.h>
#include <TlHelp32.h>
#include <array>
#include <intrin.h>
#include <functional>
#include <format>
#include <stdio.h>
#include <timeapi.h>
#include <set>
#include <list>

#include <glm/glm.hpp>

#ifndef matrxix
#define matrxix
class Matrix3x4 {
	float mat[3][4];
public:
	constexpr auto operator[](int i) const noexcept { return mat[i]; }

	constexpr void origin(vec3_t out) const noexcept;
};

constexpr void Matrix3x4::origin(vec3_t out) const noexcept
{
	out[0] = mat[0][3];
	out[1] = mat[1][3];
	out[2] = mat[2][3];
	//return vec3_t{ mat[0][3], mat[1][3], mat[2][3] };
}
#endif

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//DIRECTX
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>

//IMGUI
#include "imGui/imgui.h"
#include "imGui/imgui_impl_dx9.h"
#include "imGui/imgui_impl_win32.h"
#include "imGui/imgui_internal.h"

//detours
#include "detours/detours.h"
#pragma comment(lib, "detours.lib")

#include "koukku.hpp"

#include "entrypoint.hpp"
#include "q_math.hpp"
#include "vplane.hpp"

#include "e_enginetrace.hpp"
#include "e_collideable.hpp"
#include "gl_model_private.hpp"
#include "e_engineclient.hpp"
#include "iclientrenderable.hpp"
#include "icliententitylist.hpp"
#include "cg_local.hpp"
#include "cg_offsets.hpp"
#include "cg_init.hpp"

#include "interfaces.hpp"

#include "r_drawtools.hpp"
#include "r_init.hpp"
#include "r_ui.hpp"

#include "fs_funcs.h"
#include "fs_log.hpp"
#include "evar.h"
#include "evar_config.h"
#include "evars.h"

using namespace std::chrono_literals;

#endif //PCH_H
