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

enum PacketCmd //uint32
{
	FAIL = 0,
	SUCCESS,
	REGISTER,
	UNREGISTER,
};

//This is really needed right? or is it not?
#pragma pack(push, 1) //byte-aligned
struct Packet
{
	public:
	uint32 key;
	uint8 index;
	PacketCmd cmd;
	uint16 length;
	private:
	uint8 data;
	
	public:
	uint8 *getData()
	{
		return &data;
	}
	
	static Packet* createPacket(uint32 size)
	{
		return (Packet*)new char[size];
	}
	
	static void deletePacket(Packet *p)
	{
		return delete[] (char*)p;
	}
};
#pragma pack(pop)
#endif
