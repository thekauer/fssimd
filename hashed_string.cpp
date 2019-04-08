#include "hashed_string.h"

u32 HashedString::hash_str(std::string str)
{
	u32 h = 123456;
	u32 len = str.size();
	const u8* key = (const u8*)(&str[0]);
	if (len > 3) {
		const u32* key_x4 = (const uint32_t*)(&str[0]);
		size_t i = len >> 2;
		do {
			u32 k = *key_x4++;
			k *= 0xcc9e2d51;
			k = (k << 15) | (k >> 17);
			k *= 0x1b873593;
			h ^= k;
			h = (h << 13) | (h >> 19);
			h = h * 5 + 0xe6546b64;
		} while (--i);
		key = (const u8*)key_x4;
	}
	if (len & 3) {
		size_t i = len & 3;
		u32 k = 0;
		key = &key[i - 1];
		do {
			k <<= 8;
			k |= *key--;
		} while (--i);
		k *= 0xcc9e2d51;
		k = (k << 15) | (k >> 17);
		k *= 0x1b873593;
		h ^= k;
	}
	h ^= len;
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;
	return h;
}

HashedString::HashedString(std::string str) : hash(hash_str(str)){};
bool HashedString::operator==(const HashedString other) const{
	return hash == other.hash;
}

bool HashedString::operator!=(const HashedString other) const {
	return hash != other.hash;
}