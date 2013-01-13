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
#include <time.h>
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
	CALL,
};

#define PACKET_HEADER 4+1+4+2
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
	
	uint8 getByte(uint32 index)
	{
		return *((uint8*)(getData()+index));
	}

	uint16 getWord(uint32 index)
	{
		return *((uint16*)(getData()+index));
	}

	uint32 getDword(uint32 index)
	{
		return *((uint32*)(getData()+index));
	}

	uint64 getQword(uint32 index)
	{
		return *((uint64*)(getData()+index));
	}

	void setByte(uint32 index, uint8 input)
	{
		length += 1;
		*((uint8*)(getData()+index)) = input;
	}
	
	void setWord(uint32 index, uint16 input)
	{
		length += 2;
		*((uint16*)(getData()+index)) = input;
	}
	
	void setDword(uint32 index, uint32 input)
	{
		length += 4;
		*((uint32*)(getData()+index)) = input;
	}
	
	void setQword(uint32 index, uint64 input)
	{
		length += 8;
		*((uint64*)(getData()+index)) = input;
	}
	
	uint32 totalLength()
	{
		return length+PACKET_HEADER;
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
