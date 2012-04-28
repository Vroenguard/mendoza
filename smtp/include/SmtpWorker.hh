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
      threads::SafeQueue<int>&		_queue;
      threads::ConditionVariable<>&	_condVar;

    public:
      SmtpWorker(threads::SafeQueue<int>& queue,
	  threads::ConditionVariable<>& condVar);
  }; // SmtpWorker
} // smtp
