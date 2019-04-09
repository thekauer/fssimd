#pragma once
#ifndef __ITER_H__
#define __ITER_H__
#include "compatibility.h"
#include <xmmintrin.h>
template<typename T>
class Iter {
	using val = typename T::value_type;
	using iter =  typename T::iterator;
public:
	T arr;
	iter it,end;
	val cur;
	val next;
	val next2;
	val next3;
	Iter(iter begin,iter end) :  it(begin),end(end) {
		
		cur = *it;
		it++;
		next = *it;
		it++;
		next2 = *it;
		it++;
		next3 = *it;
		it++;
	};
	val peek() {
		return cur;
	}
	template<int N>
	val peek() {
		
		return *(it + (N - 3));
	}
	template<>
	val peek<1>() {
		return next;
	}
	template<>
	val peek<2>(){
		return next2;
	}
	template<>
	val peek<3>() {
		return next3;
	}
	val pop() {
		_mm_prefetch((const char*)&it,1);
		val r = cur;
		cur = next;
		next = next2;
		next2 = next3;
		if (it < end) {
			next3 = *it;
			it++;
		}
		return r;
	}
};


#endif