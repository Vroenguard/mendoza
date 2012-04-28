//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ATcpServer.cpp
// Creation:	Sat Apr 28 17:00:20 2012
//==============================================================================

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ATcpServer.hh"

namespace net
{
  ATcpServer::ATcpServer(Port port, size_t maxConnections)
    : _maxConnections(maxConnections)
  {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket != -1)
    {
      int option = 1;
      if (!_bind(port))
      {
	close(_socket);
	_socket = -1;
      }
      else
      {
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
      }
    }
  }

  bool ATcpServer::_bind(Port port)
  {
    sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(_socket, reinterpret_cast<sockaddr*>(&sockAddr),
	  sizeof(sockAddr)) != -1)
    {
      return true;
    }
    return false;
  }
} // net
