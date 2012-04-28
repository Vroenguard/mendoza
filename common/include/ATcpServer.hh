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
      size_t			_maxConnections;
      int			_socket;

    public:
      typedef unsigned short Port;
      ATcpServer(Port, size_t maxConnections);
      virtual ~ATcpServer(void);

    private:
      bool _bind(Port);
  }; // ATcpServer
} // net
