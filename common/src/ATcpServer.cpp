//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ATcpServer.cpp
// Creation:	Sat Apr 28 17:00:20 2012
//==============================================================================

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <cstdlib>

#include "ATcpServer.hh"

namespace net
{
  ATcpServer::ATcpServer(Port port, int maxConnections)
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
#ifdef DEBUG
	std::cout << "[DEBUG] Server successfuly initialized.\n";
#endif // DEBUG
      }
    }
  }

  ATcpServer::~ATcpServer(void)
  {
    if (this->_socket != -1)
    {
      close(this->_socket);
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

  int ATcpServer::run(void)
  {
    for (int i = 0; i < this->_maxConnections; ++i)
    {
      IWorker* worker = this->_createWorker();
      this->_workers.push_back(worker);
      worker->launch();
    }
    int clientSocket;
    sockaddr_in sockAddr;
    socklen_t sockAddrLen;

    if (listen(this->_socket, this->_maxConnections) != -1)
    {
      while ((clientSocket = accept(this->_socket,
	      reinterpret_cast<sockaddr*>(&sockAddr),
	      &sockAddrLen)) != -1)
      {
#ifdef DEBUG
	std::cout << "[DEBUG] Client accepted : launching a new worker.\n";
#endif // DEBUG
	this->_queue.push(clientSocket);
	this->_condVar.signal();
      }
    }
    else
    {
      std::cerr << "Fatal error: " << strerror(errno) << '\n';
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
} // net
