#ifndef BELL_SERVER_H
#define BELL_SERVER_H

#include "Common.h"
#include "BellSocket.h"

typedef map<socketuid_t, BellSocket*>::iterator ClientsIt;
typedef map<socketuid_t, BellSocket*> Clients;
typedef map<uint32, Clients>::iterator ClientsBellsIt;
typedef map<uint32, Clients> ClientBells;

class BellServer
{
	public:
		BellServer(uint32 keyMaster, uint32 *keyVersions, uint8 keyMax);
		~BellServer();

		void dissconectClients();
	
		// Functions
		int32 getKeyVersion(uint8 index);
		uint32 indexToKey(uint8 index);
		uint32 keyToIndex(uint32 key, uint8 index);
		void handleButton(uint8 buttonNo);
		
		bool registerClient(uint32 key, socketuid_t uid, BellSocket *socket);
		bool unregisterClient(uint32 key, socketuid_t uid);
		
	private:
		uint32 *keyVersions_;
		uint32 keyMaster_;
		uint8 keyMax_;
	
		vector<BellSocket*> bells_;
		ClientBells clientBells_;
};
extern BellServer* bellServer;

#endif
