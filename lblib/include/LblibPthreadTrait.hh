#pragma once

#include "LblibCompilation.hh"
#ifdef LBLIB_PLATFORM_LINUX

# include <pthread.h>
# include "LblibPthreadApi.hpp"

namespace lblib
{
  namespace threads
  {
    class PthreadTrait
    {
      private:
	PthreadTrait(void);
	PthreadTrait(PthreadTrait const&);

      public:
	typedef pthread_t			Handle;
	typedef pthread_mutex_t			MutexHandle;
	typedef PthreadApi<PthreadTrait>	Api;
	typedef pthread_cond_t			CondHandle;
    };

    typedef PthreadTrait DefaultThreadTrait;
  }
}

#endif // LBLIB_PLATFORM_LINUX
