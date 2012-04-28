//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	IWorker.hh
// Creation:	Sat Apr 28 18:14:37 2012
//==============================================================================

#pragma once

#include <vector>
#include "LblibAThread.hpp"

namespace threads = lblib::threads;

namespace net
{
  class IWorker : public threads::Thread
  {
    public:
      virtual ~IWorker(void) {}

    protected:
      virtual void run(void) = 0;
  }; // IWorker
} // net
