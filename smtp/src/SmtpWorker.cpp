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
    : _queue(queue), _condVar(condVar)
  {
  }
} // smtp
