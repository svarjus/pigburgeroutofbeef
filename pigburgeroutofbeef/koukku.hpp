#pragma once

#ifndef koukku_
#define koukku_
#include "pch.h"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

namespace VirtualMethod
{
	template <typename T, std::size_t Idx, typename ...Args>
	constexpr T call(void* classBase, Args... args) noexcept
	{
		return (*reinterpret_cast<T(__thiscall***)(void*, Args...)>(classBase))[Idx](classBase, args...);
	}
}

#define VIRTUAL_METHOD(returnType, name, idx, args, argsRaw) \
returnType name args noexcept \
{ \
    return VirtualMethod::call<returnType, idx>argsRaw; \
}


struct hook //a VERY basic structure to do the most basic things!
{

	LONG install(PVOID* ppPointer, PVOID pDetour);
	LONG remove(PVOID* ppPointer, PVOID pDetour);

	void nop(std::uintptr_t address);
	void write_addr(void* addr, const char* bytes, size_t len);
	void write_addr(void* addr, void* bytes, size_t len);

	void write_addr(std::uintptr_t addr, const char* bytes, size_t len);
	void memcopy(void* dst, void* src, size_t len);

	void get_bytes(void* addr, size_t len, BYTE* buffer);

	std::uintptr_t find_pattern(std::string moduleName, std::string pattern);
	std::uintptr_t find_pattern(DWORD start_address, DWORD end_address, std::string pattern);


};

#endif