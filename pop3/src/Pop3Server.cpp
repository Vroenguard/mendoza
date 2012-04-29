//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	Pop3Server.cpp
// Creation:	Sun Apr 29 01:09:29 2012
//==============================================================================

#include <iostream>

#include "Pop3Server.hh"
#include "Pop3Worker.hh"

namespace pop3
{
  Pop3Server::Pop3Server(Port port, int maxConnections)
    : net::ATcpServer(port, maxConnections)
  {
  }

  Pop3Server::~Pop3Server(void)
  {
  }

  net::IWorker* Pop3Server::_createWorker(void)
  {
#ifdef DEBUG
    std::cout << "[DEBUG] Creating a new SMTP worker.\n";
#endif // DEBUG
    return new Pop3Worker(this->_queue, this->_condVar);
  }
} // pop3
