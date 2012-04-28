//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	SmtpServer.hh
// Creation:	Sun Apr 29 01:08:14 2012
//==============================================================================

#pragma once

#include "ATcpServer.hh"
#include "IWorker.hh"

namespace smtp
{
  class SmtpServer : public net::ATcpServer
  {
    public:
      using net::ATcpServer::Port;
      SmtpServer(Port port, int maxConnections);
      virtual ~SmtpServer(void);

    protected:
      net::IWorker* _createWorker(void);

    private:
      SmtpServer(SmtpServer const&);
      SmtpServer const& operator = (SmtpServer const&);
  };
} // smtp
