//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	SmtpWorker.hh
// Creation:	Sat Apr 28 22:00:19 2012
//==============================================================================

#pragma once

#include "LblibSafeQueue.hpp"
#include "LblibConditionVariable.hpp"

#include "IWorker.hh"

namespace threads = lblib::threads;

namespace smtp
{
  class SmtpWorker : public net::IWorker
  {
    private:
      typedef void (SmtpWorker::*Action)(void);

      threads::SafeQueue<int>&		_queue;
      threads::ConditionVariable<>&	_condVar;
      Action				_nextAction;

    public:
      SmtpWorker(threads::SafeQueue<int>& queue,
	  threads::ConditionVariable<>& condVar);

    protected:
      virtual void run(void);

      SmtpWorker(SmtpWorker const&);
      SmtpWorker const& operator = (SmtpWorker const&);
  }; // SmtpWorker
} // smtp
