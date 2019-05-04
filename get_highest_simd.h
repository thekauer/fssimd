

#ifdef _WIN32
#include <intrin.h>
//  Windows
#define cpuid(info, x)    __cpuidex(info, x, 0)

#else

//  GCC Intrinsics
#include <cpuid.h>
void cpuid(int info[4], int InfoType) {
	__cpuid_count(InfoType, 0, info[0], info[1], info[2], info[3]);
}

#endif

int get_highest_supported_simd() {
	bool SSE2, AVX;
	int info[4];
	cpuid(info, 0);
	int nIds = info[0];

	cpuid(info, 0x80000000);
	unsigned nExIds = info[0];

	//  Detect Features
	if (nIds >= 0x00000001) {
		cpuid(info, 0x00000001);
		SSE2 = (info[3] & ((int)1 << 26)) != 0;
		AVX = (info[2] & ((int)1 << 28)) != 0;

	}
	return AVX ? 2 : SSE2 ? 1 : 0;
}