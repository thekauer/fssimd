#pragma  once
#ifndef __SIMD_H__
#define __SIMD_H__

#include "compatibility.h"
template<typename M,typename R>
class ISimd {
public:
    using msk = M;
    using reg = R;
    virtual INLINE msk load(const msk*)=0;
    virtual INLINE reg movemask(const msk&)=0;
    virtual INLINE msk cmpeq(const msk&,const msk&)=0;
    virtual INLINE msk set(char)=0;

};


#include <emmintrin.h>
class SSE2 : public ISimd<__m128i,u32> {
public:
    INLINE msk load(const msk* addr) override {
        return _mm_loadu_si128(addr);
    }
    INLINE reg movemask(const msk& mask) override {
        return _mm_movemask_epi8(mask);
    }
    INLINE msk cmpeq(const msk& m1,const msk& m2) override {
        return _mm_cmpeq_epi8(m1,m2);
    }
    INLINE msk set(char c) override {
        return _mm_set1_epi8(c);
    }

};

#include <immintrin.h>
class AVX : public ISimd<__m256i,u32> {
public:
    INLINE msk load(const msk* addr) override {
        return _mm256_loadu_si256(addr);
    }
    INLINE reg movemask(const msk& mask) override {
        return _mm256_movemask_epi8(mask);
    }
    INLINE msk cmpeq(const msk& m1,const msk& m2) override {
        return _mm256_cmpeq_epi8(m1,m2);
    }
    INLINE msk set(char c) override {
        return _mm256_set1_epi8(c);
    }
};


#ifdef __ARM_NEON__
#include <arm_neon.h>
class Neon : public ISimd<uint8x16_t,u32> {
public:
    INLINE msk load(const msk* addr) override {
        return vld1q_u8(addr);

    }
    INLINE reg movemask(const msk& mask) override {
        const u8 ALIGN(16) _Powers[16] = {1,2,4,8,16,32,64,128,1,2,4,8,16,32,64,128};
        uint8x16_t Powers = load(_Powers);
        uint64x2_t Mask = vpaddlq_u32(vpaddlq_u16(vpaddlq_u8(vandq_u8(mask,Powers))));
        uint16_t output;
        vst1q_lane_u8((u8*)&output+0,(uint8x16_t)Mask,0);
        vst1q_lane_u8((u8*)&output+1,(uint8x16_t)Mask,8);
        return (u32)output;
    }
    INLINE msk cmpeq(const msk& m1,const msk& m2) override {
        return vceqq_u8(m1,m2);
    }
    INLINE msk set(char c) {
        return vdupq_n_u8(c);
    }
};
#endif //__ARM_NEON__

/*
template<typename S,typename T,size_t SZ = sizeof(S::msk),typename R = typename S::reg,typename It = typename T::iterator,typename V=typename T::value_type>
V match(V val,It beg,It end) {
    S s;
    auto len = std::distance(beg,end);
    R r;
    ptr i=0;
    do {
        r = s.movemask(s.cmpeq(s.set(val),s.load( (typename S::msk*)&beg[0])));
        len-=SZ;
        i++;
    }while(len>SZ);
    return ((V*)&beg[0])[r+i*SZ];
}
*/

template<typename S,typename T>
T match(T* arr,T val) {
    S s;
    return s.movemask(s.cmpeq(s.set(val),s.load( (typename S::msk*)arr)))-1;
}

#endif
