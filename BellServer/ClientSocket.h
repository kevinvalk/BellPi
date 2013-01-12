#include <TcpSocket.h>
#include <ISocketHandler.h>

class ClientSocket : public TcpSocket
{
public:
	ClientSocket(ISocketHandler& );

	void OnRead();
};
