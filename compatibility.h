#pragma once
#ifndef __COMPATIBILITY_H__
#define __COMPATIBILITY_H__

#ifdef __clang__ || __GNUC__
#define INLINE static inline __attribute__((__always_inline__))
#define ALIGN(_n,_decl) _decl __attribute__((aligned(_n)))
#endif
#ifdef _MSVC_VER
#define INLINE __forceinline
#define ALIGN(_n,_decl) __declspec(align(_n)) _decl
#endif

#ifdef _WIN32
#define cpuid(info, x)    __cpuidex(info, x, 0)
#else
#include <cpuid.h>
void cpuid(int info[4], int InfoType){
    __cpuid_count(InfoType, 0, info[0], info[1], info[2], info[3]);
}
#endif

#endif