//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	SmtpWorker.cpp
// Creation:	Sat Apr 28 22:07:49 2012
//==============================================================================

#include "SmtpWorker.hh"

namespace smtp
{
  SmtpWorker::SmtpWorker(threads::SafeQueue<int>& queue,
      threads::ConditionVariable<>& condVar)
    : _queue(queue), _condVar(condVar), _nextAction(NULL)
  {
  }

  void SmtpWorker::run(void)
  {
    this->_condVar.wait();
    while (42)
    {
      if (this->_nextAction)
      {
	(this->*_nextAction)();
      }
    }
  }
} // smtp
