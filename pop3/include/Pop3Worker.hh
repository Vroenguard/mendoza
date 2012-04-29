//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	Pop3Worker.hh
// Creation:	Sat Apr 28 22:00:19 2012
//==============================================================================

#pragma once

#include <list>

#include "LblibSafeQueue.hpp"
#include "LblibConditionVariable.hpp"

#include "IWorker.hh"
#include "ClientSocket.hh"

namespace threads = lblib::threads;

namespace pop3
{
  class Pop3Worker : public net::IWorker
  {
    private:
      typedef void (Pop3Worker::*Action)(void);
      typedef std::list<std::string> RecipientList;

      threads::SafeQueue<int>&		_queue;
      threads::ConditionVariable<>&	_condVar;
      Action				_nextAction;
      net::ClientSocket			_socket;
      std::string			_line;
      char const*			_eol;

    public:
      Pop3Worker(threads::SafeQueue<int>& queue,
	  threads::ConditionVariable<>& condVar);

    protected:
      virtual void run(void);

      Pop3Worker(Pop3Worker const&);
      Pop3Worker const& operator = (Pop3Worker const&);
  }; // Pop3Worker
} // pop3
