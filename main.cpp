#include <iostream>
#include <Windows.h>
#include <immintrin.h>
#include <chrono>
#include <string>
#include <algorithm>
#include <random>


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




struct Lexem {
	const enum t_ {
		Op,
		Lit,
		Sep,
		Kw,
		Id
	}type;
	Lexem(t_ type) : type(type){};
};


struct Sep : Lexem {
	const enum t_ {
		Space,
		Tab,
		NewLine
	} type;
	Sep(t_ type) : type(type), Lexem(Lexem::Sep){};
};

struct Lit : Lexem {
	const enum t_ {
		Int,
		Bool,
		Char,
		String,
		Float,
		Range
	} type;
	Lit(t_ type) : type(type),Lexem(Lexem::Lit) {};
};


struct Kw : Lexem {
	const enum t_ {
		For
	} type;
	Kw(t_ type) : type(type), Lexem(Lexem::Kw) {};
};


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


/*
__forceinline __m256i fill8(char c) {
	return _mm256_setr_epi8(c, c, c, c,
		c, c, c, c,

		c, c, c, c,
		c, c, c, c,
		
		c, c, c, c,
		c, c, c, c,
		
		c, c, c, c,
		c, c, c, c);
}
*/
/*
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
*/
/*
u8 avx(char c) {
	//auto&a = _mm256_loadu_si256((const __m256i*)&cmpa);
	//__m256i a = _mm256_loadu_si256((const __m256i*)&cmpa);
	auto&b = _mm256_setr_epi8(c, c, c, c,

		c, c, c, c,
		c, c, c, c,

		c, c, c, c,
		c, c, c, c,

		c, c, c, c,
		c, c, c, c,
		c,c,c,c);

	auto& cmp = _mm256_cmpeq_epi8(a, b);
	auto m =_mm256_movemask_epi8(cmp);
	return __lzcnt(m);

}*/


u8 sse2(char c) {

	return __lzcnt(_mm_movemask_epi8(_mm_cmpeq_epi8(
		_mm_loadu_si128((const __m128i*)&cmpa),
		_mm_setr_epi8(c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c)
		)));
}


#define bench(f,c) _bench(f,#f,c)

int main() {

	
	bench(classic, test);
	bench(sse2, test);
	//bench(swar, "swar");


	std::cin.get();
	return 0;
}