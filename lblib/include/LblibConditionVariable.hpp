#pragma once

#include <pthread.h>

#include "LblibScopedLock.hpp"
#include "MLblibutex.hpp"

namespace lblib
{
  namespace threads
  {
    template <typename Trait = LinuxTrait::ThreadTrait>
    class ConditionVariable
    {
      private:
	typedef typename Trait::CondHandle	CondHandle;
	typedef typename Trait::Api		ThreadApi;

	CondHandle		_handle;
	Mutex<Trait>		_mutex;
	bool			_initialized;

	ConditionVariable(ConditionVariable<Trait> const&);
	ConditionVariable const& operator = (ConditionVariable<Trait> const&);

      public:
	ConditionVariable(void);
	~ConditionVariable(void);

	bool signal(void);
	bool broadcast(void);
	bool wait(void);
	bool timedWait(void);
    };

    template <typename Trait>
      ConditionVariable<Trait>::ConditionVariable(void)
      {
	if (ThreadApi::condVarInit(this->_handle))
	  this->_initialized = true;
	else
	  this->_initialized = false;
      }

    template <typename Trait>
      ConditionVariable<Trait>::~ConditionVariable(void)
      {
	if (this->_initialized)
	  ThreadApi::condVarDestroy(this->_handle);
      }

    template <typename Trait>
      inline bool ConditionVariable<Trait>::signal(void)
      {
	if (this->_initialized)
	{
	  if (ThreadApi::condVarSignal(this->_handle))
	    return true;
	}
	return false;
      }

    template <typename Trait>
      inline bool ConditionVariable<Trait>::broadcast(void)
      {
	if (this->_initialized && ThreadApi::condVarBroadCast(this->_handle))
	  return true;
	else
	  return false;
      }

    template <typename Trait>
      inline bool ConditionVariable<Trait>::wait(void)
      {
	if (this->_initialized)
	{
	  ScopedLock<Trait> lock(this->_mutex);
	  if (ThreadApi::condVarWait(this->_handle, this->_mutex.getRawMutex()))
	    return true;
	}
	return false;
      }
  } // threads
} // lblib
