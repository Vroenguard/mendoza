//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	SmtpServer.cpp
// Creation:	Sun Apr 29 01:09:29 2012
//==============================================================================

#include <iostream>

#include "SmtpServer.hh"
#include "SmtpWorker.hh"

namespace smtp
{
  SmtpServer::SmtpServer(Port port, int maxConnections)
    : net::ATcpServer(port, maxConnections)
  {
  }

  SmtpServer::~SmtpServer(void)
  {
  }

  net::IWorker* SmtpServer::_createWorker(void)
  {
#ifdef DEBUG
    std::cout << "[DEBUG] Creating a new SMTP worker.\n";
#endif // DEBUG
    return new SmtpWorker(this->_queue, this->_condVar);
  }
} // smtp
