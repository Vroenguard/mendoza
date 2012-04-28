//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ATcpServer.hh
// Creation:	Sat Apr 28 16:54:02 2012
//==============================================================================

#pragma once

#include <list>

#include "LblibSafeQueue.hpp"
#include "LblibConditionVariable.hpp"
#include "IWorker.hh"

namespace threads = lblib::threads;

namespace net
{
  class ATcpServer
  {
    protected:
      typedef std::list<IWorker*> WorkerList;

      threads::SafeQueue<int>		_queue;
      int				_maxConnections;
      int				_socket;
      WorkerList			_workers;
      threads::ConditionVariable<>	_condVar;

    public:
      typedef unsigned short Port;
      ATcpServer(Port, int maxConnections);
      virtual ~ATcpServer(void);

      void run(void);

    protected:
      virtual IWorker* _createWorker(void) = 0;

    private:
      ATcpServer(ATcpServer const&);
      ATcpServer const& operator = (ATcpServer const&);

      bool _bind(Port);
  }; // ATcpServer
} // net
