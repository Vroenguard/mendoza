//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	AWorker.hh
// Creation:	Sat Apr 28 18:14:37 2012
//==============================================================================

#pragma once

#include <vector>
#include "LblibAThread.hpp"

namespace threads = lblib::threads;

namespace net
{
  template <typename State>
  class AWorker : public threads::Thread
  {
    protected:
      typedef void (AWorker::*Action)(void);
      typedef std::vector<Action> ActionMap;

      State	_currentState;
      ActionMap	_actions;

    public:
      AWorker(void);
      virtual ~AWorker(void);

    private:
      AWorker(AWorker const&);
      AWorker const& operator = (AWorker const&);
  }; // AWorker
} // net
