//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ATcpServer.hh
// Creation:	Sat Apr 28 16:54:02 2012
//==============================================================================

#pragma once

#include <list>
#include "LblibSafeQueue.hpp"
#include "IWorker.hh"

namespace threads = lblib::threads;

namespace net
{
  class ATcpServer
  {
    private:
      threads::SafeQueue<int>	_queue;
      int			_maxConnections;
      int			_socket;

      typedef std::list<IWorker*> WorkerList;
      WorkerList		_workers;

    public:
      typedef unsigned short Port;
      ATcpServer(Port, size_t maxConnections);
      virtual ~ATcpServer(void);

      void run(void);

    protected:
      virtual IWorker* createWorker(void) = 0;

    private:
      ATcpServer(ATcpServer const&);
      ATcpServer const& operator = (ATcpServer const&);

      bool _bind(Port);
  }; // ATcpServer
} // net
