#pragma once

#include "LblibMutex.hpp"

namespace lblib
{
  namespace threads
  {
    template <typename Trait = DefaultThreadTrait>
    class ScopedLock
    {
      private:
	Mutex<Trait>&	_mutex;
	bool		_locked;

      public:
	ScopedLock(Mutex<Trait>& mutex) :
	  _mutex(mutex)
	{
	  this->_locked = this->_mutex.lock();
	}

	~ScopedLock(void)
	{
	  if (this->_locked)
	    this->_mutex.unlock();
	}

	bool isLocked(void) const
	{
	  return this->_locked;
	}

	operator bool(void) const
	{
	  return this->_locked;
	}

	bool operator !(void) const
	{
	  return !this->_locked;
	}
    };
  } // namespace threads
} // namespace lblib
