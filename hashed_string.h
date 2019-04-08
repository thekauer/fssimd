#pragma once
#ifndef __HASHED_STRING_H__
#define __HASHED_STRING_H__
#include <iostream>
#include "compatibility.h"
class HashedString {
	const u32 hash;
	u32 hash_str(std::string);
public:
	HashedString(std::string str);
	bool operator==(const HashedString) const;
	bool operator!=(const HashedString) const;
};


#endif