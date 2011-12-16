/*
 * Copyright (C) 2005-2011 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010-2011 ProjectSkyfire <http://www.projectskyfire.org/>
 * 
 * Copyright (C) 2011 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef ARKCORE_BYTECONVERTER_H
#define ARKCORE_BYTECONVERTER_H

/** ByteConverter reverse your byte order.  This is use
 for cross platform where they have different endians.
 */

#include "Define.h"
#include<algorithm>

namespace ByteConverter {
template<size_t T>
inline void convert(char *val) {
	std::swap(*val, *(val + T - 1));
	convert<T - 2>(val + 1);
}

template<> inline void convert<0>(char *) {
}
template<> inline void convert<1>(char *) {
} // ignore central byte

template<typename T> inline void apply(T *val) {
	convert<sizeof(T)>((char *) (val));
}
}

#if ARKCORE_ENDIAN == ARKCORE_BIGENDIAN
template<typename T> inline void EndianConvert(T& val) {
	ByteConverter::apply<T>(&val);
}
template<typename T> inline void EndianConvertReverse(T&) {
}
#else
template<typename T> inline void EndianConvert(T&) {}
template<typename T> inline void EndianConvertReverse(T& val) {ByteConverter::apply<T>(&val);}
#endif

template<typename T> void EndianConvert(T*); // will generate link error
template<typename T> void EndianConvertReverse(T*); // will generate link error

inline void EndianConvert(uint8&) {
}
inline void EndianConvert(int8&) {
}
inline void EndianConvertReverse(uint8&) {
}
inline void EndianConvertReverse(int8&) {
}

#endif
