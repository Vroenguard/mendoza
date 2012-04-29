//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	Pop3Server.hh
// Creation:	Sun Apr 29 01:08:14 2012
//==============================================================================

#pragma once

#include "ATcpServer.hh"
#include "IWorker.hh"

namespace pop3
{
  class Pop3Server : public net::ATcpServer
  {
    public:
      using net::ATcpServer::Port;
      Pop3Server(Port port = 10110, int maxConnections = 42);
      virtual ~Pop3Server(void);

    protected:
      net::IWorker* _createWorker(void);

    private:
      Pop3Server(Pop3Server const&);
      Pop3Server const& operator = (Pop3Server const&);
  };
} // pop3
