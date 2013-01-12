#include "BellServer.h"

BellServer::BellServer(uint32 keyMaster, uint32 *keyVersions, uint32 keyMax)
{
	keyMaster_ = keyMaster;
	keyVersions_ = keyVersions;
	keyMax_ = keyMax;
	
	printf("BellServer with master key: %08X\n", keyMaster);
	
	for(uint32 i = 0; i < keyMax_; i++)
	{
		uint32 clientKey = indexToKey(i, keyMaster_, getKeyVersion(i));
		uint32 clientIndex = keyToIndex(clientKey, keyMaster_, getKeyVersion(i));
		
		printf("Client %i (version: %i) with key %08X, decrypted key: %i\n", (i+1), getKeyVersion(i), clientKey, clientIndex);
		
		if(clientIndex != i)
		{
			printf("There is an error in the key algorithm, EXIT!");
			exit(1);
		}
	}
}

BellServer::~BellServer()
{

}

int32 BellServer::getKeyVersion(uint32 index)
{
	if(index < keyMax_)
		return keyVersions_[index];
	return -1;
}

uint32 BellServer::indexToKey(uint32 index, uint32 keyMaster, uint32 version)
{
	return (((index << (32 - keyMax_)) ^ keyMaster) ^ version);
}

uint32 BellServer::keyToIndex(uint32 key, uint32 keyMaster, uint32 version)
{
	return ((key ^ version) ^ keyMaster) >> (32 - keyMax_);
}
		
void BellServer::dissconectClients()
{
	for(uint32 i = 0; i < bellSockets_.size(); i++)
	{
		BellSocket* bellSocket = bellSockets_.at(i);
		bellSocket->quit(); //stop the thread
	}
}
