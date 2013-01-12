#ifndef COMMON_H
#define COMMON_H

//typedef
typedef long long           int128;
typedef long                int64;
typedef int                 int32;
typedef short               int16;
typedef char                int8;
typedef unsigned long long  uint128;
typedef unsigned long       uint64;
typedef unsigned int        uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>

// Usings's
using std::vector;
using std::map;

//This is really needed right? or is it not?
#pragma pack(push, 1) //byte-aligned
struct Packet
{

};
#pragma pack(pop)
#endif
