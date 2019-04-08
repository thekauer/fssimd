#pragma once
#ifndef __ITER_H__
#define __ITER_H__
#include "compatibility.h"
template<typename T>
class Iter {
	T arr;
	using val = T::value_type;
	using iter = T::iterator;
	iter it;
	val next;
	val next2;
	val next3;
protected:
	Iter(T arr) : arr(arr) {};
	val peek() {
		return *it;
	}
	val peek(unsigned int n) {
		return *(it + n*sizeof(val));
	}
	val pop() {
		prefetch(it);
		return *it++;
	}
};


#endif