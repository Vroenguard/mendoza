//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ATcpServer.hh
// Creation:	Sat Apr 28 16:54:02 2012
//==============================================================================

#pragma once

#include "LblibSafeQueue.hpp"

namespace threads = lblib::threads;

namespace net
{
  class ATcpServer
  {
    private:
      threads::SafeQueue<int>	_queue;
      int			_maxConnections;
      int			_socket;

    public:
      typedef unsigned short Port;
      ATcpServer(Port, size_t maxConnections);
      virtual ~ATcpServer(void);

      void run(void);

    private:
      ATcpServer(ATcpServer const&);
      ATcpServer const& operator = (ATcpServer const&);

      bool _bind(Port);
  }; // ATcpServer
} // net
