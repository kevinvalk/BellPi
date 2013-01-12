#include "BellServer.h"

BellServer::BellServer(uint32 keyMaster, uint32 *keyVersions, uint8 keyMax)
{
	keyMaster_ = keyMaster;
	keyVersions_ = keyVersions;
	keyMax_ = keyMax;
	
	printf("BellServer with master key: %08X\n", keyMaster);
	
	// Build all keys for all clients
	for(uint8 i = 0; i < keyMax_; i++)
	{
		uint32 clientKey = indexToKey(i);
		uint32 clientIndex = keyToIndex(clientKey, i);
		
		printf("Client %i (version: %i) with key %08X, decrypted key: %i\n", i, getKeyVersion(i), clientKey, clientIndex);
		
		if(clientIndex != i)
		{
			printf("There is an error in the key algorithm, EXIT!");
			exit(1);
		}
		
		// Add it to the list
		clientBells_[clientKey][0] = NULL;
	}
}

BellServer::~BellServer()
{

}

int32 BellServer::getKeyVersion(uint8 index)
{
	if(index < keyMax_)
		return keyVersions_[index];
	return -1;
}

uint32 BellServer::indexToKey(uint8 index)
{
	return (((index << (32 - keyMax_)) ^ keyMaster_) ^ getKeyVersion(index));
}

uint32 BellServer::keyToIndex(uint32 key, uint8 index)
{
	return ((key ^ getKeyVersion(index)) ^ keyMaster_) >> (32 - keyMax_);
}

void BellServer::handleButton(uint8 buttonNo)
{
	switch(buttonNo)
	{
		case 6:
			printf("Call all\n");
		break;
		default:
			uint32 key = indexToKey(buttonNo);
			printf("Calling client %i with key: %08X\n", buttonNo, key);
			Clients *bells = &clientBells_[key];
			
			// Go through all client attached to this bell
			for(ClientsIt it=bells->begin(); it!=bells->end(); it++)
			{
				if(it->first == 0) continue;
				BellSocket *socket = it->second;
				socket->handleCall();
			}
		break;
	}
}

bool BellServer::registerClient(uint32 key, socketuid_t uid, BellSocket *socket)
{
	ClientsIt clientIt;
	ClientsBellsIt bellIt;
	
	// Skip uid == 0 as that is reserved
	if(uid == 0)
		return false;
	
	// Check if this key even exists
	bellIt = clientBells_.find(key);
	if(bellIt == clientBells_.end())
	{
		printf("This key does not exists!\n");
		return false;
	}
	
	// Check if it already exists if so we can not register you
	Clients *bells = &clientBells_[key];
	clientIt = bells->find(uid);
	if(clientIt != bells->end())
		return false;
	
	// Register this socket
	(*bells)[uid] = socket;
	return true;
}

bool BellServer::unregisterClient(uint32 key, socketuid_t uid)
{
	Clients *bells = &clientBells_[key];
	return bells->erase(uid);
}

void BellServer::dissconectClients()
{
	for(uint32 i = 0; i < bells_.size(); i++)
	{
		BellSocket* bellSocket = bells_.at(i);
		bellSocket->quit(); //stop the thread
	}
}
