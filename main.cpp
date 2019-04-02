#include <iostream>
#include <immintrin.h>
#include <chrono>
#include <string>

#define cpuid(info, x)    __cpuidex(info, x, 0)
#define p(b) std::cout << #b << ": "<< std::boolalpha << b << "\n";












typedef unsigned char u8;

typedef u8(*f)(char);

void _bench(f fun, std::string name, char c) {
	u8 res;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 9999999; ++i)res = fun(c);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << name << "\nresult: " << (int)res << "\ntime: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "\n\n";
}

const char test = 'g';




u8 classic(char c) {
	switch (c)
	{
	case 'g':
		return 16;
	case 'h':
		return 17;
	case 'i':
		return 18;
	case 'j':
		return 19;
	case 'k':
		return 20;
	case 'l':
		return 21;
	case 'm':
		return 22;
	case 'n':
		return 23;
	case 'o':
		return 24;
	case 'p':
		return 25;
	case 'q':
		return 26;
	case 'r':
		return 27;
	case 's':
		return 28;
	case 't':
		return 29;
	case 'u':
		return 30;
	case 'v':
		return 31;
	default:
		return ~0;
	}
}

u8 classic_32(char c) {
	switch (c)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'a':
		return 10;
	case 'b':
		return 11;
	case 'c':
		return 12;
	case 'd':
		return 13;
	case 'e':
		return 14;
	case 'f':
		return 15;
	case 'g':
		return 16;
	case 'h':
		return 17;
	case 'i':
		return 18;
	case 'j':
		return 19;
	case 'k':
		return 20;
	case 'l':
		return 21;
	case 'm':
		return 22;
	case 'n':
		return 23;
	case 'o':
		return 24;
	case 'p':
		return 25;
	case 'q':
		return 26;
	case 'r':
		return 27;
	case 's':
		return 28;
	case 't':
		return 29;
	case 'u':
		return 30;
	case 'v':
		return 31;


	default:
		return ~0;
	}
}

u8 __declspec(align(16)) cmpa[32] = { 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30 };


u8 avx(char c) {
	return __lzcnt(_mm256_movemask_epi8(_mm256_cmpeq_epi8(
		_mm256_loadu_si256((__m256i*)&cmpa),
		_mm256_setr_epi8(c, c, c, c,
		c, c, c, c,

		c, c, c, c,
		c, c, c, c,

		c, c, c, c,
		c, c, c, c,

		c, c, c, c,
		c, c, c, c)
		)));
}

u8 sse2(char c) {

	return __lzcnt(_mm_movemask_epi8(_mm_cmpeq_epi8(
		_mm_loadu_si128((const __m128i*)&cmpa),
		_mm_setr_epi8(c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c)
		)));
}


#define bench(f,c) _bench(f,#f,c)





int main() {

	//  Misc.
	bool HW_MMX;
	bool HW_x64;
	bool HW_ABM;      // Advanced Bit Manipulation
	bool HW_RDRAND;
	bool HW_BMI1;
	bool HW_BMI2;
	bool HW_ADX;
	bool HW_PREFETCHWT1;

	//  SIMD: 128-bit
	bool HW_SSE;
	bool HW_SSE2;
	bool HW_SSE3;
	bool HW_SSSE3;
	bool HW_SSE41;
	bool HW_SSE42;
	bool HW_SSE4a;
	bool HW_AES;
	bool HW_SHA;

	//  SIMD: 256-bit
	bool HW_AVX;
	bool HW_XOP;
	bool HW_FMA3;
	bool HW_FMA4;
	bool HW_AVX2;

	//  SIMD: 512-bit
	bool HW_AVX512F;    //  AVX512 Foundation
	bool HW_AVX512CD;   //  AVX512 Conflict Detection
	bool HW_AVX512PF;   //  AVX512 Prefetch
	bool HW_AVX512ER;   //  AVX512 Exponential + Reciprocal
	bool HW_AVX512VL;   //  AVX512 Vector Length Extensions
	bool HW_AVX512BW;   //  AVX512 Byte + Word
	bool HW_AVX512DQ;   //  AVX512 Doubleword + Quadword
	bool HW_AVX512IFMA; //  AVX512 Integer 52-bit Fused Multiply-Add
	bool HW_AVX512VBMI; //  AVX512 Vector Byte Manipulation Instructions

	int info[4];
	cpuid(info, 0);
	int nIds = info[0];

	cpuid(info, 0x80000000);
	unsigned nExIds = info[0];

	//  Detect Features
	if (nIds >= 0x00000001){
		cpuid(info, 0x00000001);
		HW_MMX = (info[3] & ((int)1 << 23)) != 0;
		HW_SSE = (info[3] & ((int)1 << 25)) != 0;
		HW_SSE2 = (info[3] & ((int)1 << 26)) != 0;
		HW_SSE3 = (info[2] & ((int)1 << 0)) != 0;

		HW_SSSE3 = (info[2] & ((int)1 << 9)) != 0;
		HW_SSE41 = (info[2] & ((int)1 << 19)) != 0;
		HW_SSE42 = (info[2] & ((int)1 << 20)) != 0;
		HW_AES = (info[2] & ((int)1 << 25)) != 0;

		HW_AVX = (info[2] & ((int)1 << 28)) != 0;
		HW_FMA3 = (info[2] & ((int)1 << 12)) != 0;

		HW_RDRAND = (info[2] & ((int)1 << 30)) != 0;
	}
	if (nIds >= 0x00000007){
		cpuid(info, 0x00000007);
		HW_AVX2 = (info[1] & ((int)1 << 5)) != 0;

		HW_BMI1 = (info[1] & ((int)1 << 3)) != 0;
		HW_BMI2 = (info[1] & ((int)1 << 8)) != 0;
		HW_ADX = (info[1] & ((int)1 << 19)) != 0;
		HW_SHA = (info[1] & ((int)1 << 29)) != 0;
		HW_PREFETCHWT1 = (info[2] & ((int)1 << 0)) != 0;

		HW_AVX512F = (info[1] & ((int)1 << 16)) != 0;
		HW_AVX512CD = (info[1] & ((int)1 << 28)) != 0;
		HW_AVX512PF = (info[1] & ((int)1 << 26)) != 0;
		HW_AVX512ER = (info[1] & ((int)1 << 27)) != 0;
		HW_AVX512VL = (info[1] & ((int)1 << 31)) != 0;
		HW_AVX512BW = (info[1] & ((int)1 << 30)) != 0;
		HW_AVX512DQ = (info[1] & ((int)1 << 17)) != 0;
		HW_AVX512IFMA = (info[1] & ((int)1 << 21)) != 0;
		HW_AVX512VBMI = (info[2] & ((int)1 << 1)) != 0;
	}
	if (nExIds >= 0x80000001){
		cpuid(info, 0x80000001);
		HW_x64 = (info[3] & ((int)1 << 29)) != 0;
		HW_ABM = (info[2] & ((int)1 << 5)) != 0;
		HW_SSE4a = (info[2] & ((int)1 << 6)) != 0;
		HW_FMA4 = (info[2] & ((int)1 << 16)) != 0;
		HW_XOP = (info[2] & ((int)1 << 11)) != 0;
	}


	p(HW_SSE);
	p(HW_SSE2);
	p(HW_SSE3);
	p(HW_SSSE3);
	p(HW_x64);
	p(HW_AES);
	p(HW_AVX);
	p(HW_AVX2);
	p(HW_AVX512F);
	std::cout << "\n\n";

	char test = 'q';
	bench(classic, test);
	bench(classic_32, test);
	bench(sse2, test);
	bench(avx, test);

	std::cin.get();
	return 0;
}