#ifndef BELL_SERVER_H
#define BELL_SERVER_H

#include "BellSocket.h"
#include "Common.h"

typedef vector<BellSocket*> BellSockets;
class BellServer
{
	public:
		BellServer(uint32 keyMaster, uint32 *keyVersions, uint32 keyMax);
		~BellServer();

		void dissconectClients();
	
	private:
		uint32 *keyVersions_;
		uint32 keyMaster_;
		uint32 keyMax_;
	
		BellSockets bellSockets_;
		map<uint32, BellSockets> bells_;
		
		// Functions
		int32 getKeyVersion(uint32 index);
		uint32 indexToKey(uint32 index, uint32 keyMaster, uint32 version);
		uint32 keyToIndex(uint32 key, uint32 keyMaster, uint32 version);
};
extern BellServer* bellServer;

#endif
