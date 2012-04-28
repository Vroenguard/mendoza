#pragma once

#include "LblibLinuxTrait.hh"

namespace lblib
{
  namespace threads
  {
    template <typename Trait> class ConditionVariable;

    template <typename Trait = DefaultTrait::ThreadTrait>
      class Mutex
      {
	private:
	  typedef typename Trait::MutexHandle	MutexHandle;
	  typedef typename Trait::Api		ThreadApi;

	  MutexHandle		_handle;
	  bool			_isInitialized;

	private:
	  // Le copie et la duplication sont interdites :
	  Mutex(Mutex const&);
	  Mutex const& operator = (Mutex const&);

	public:
	  /**
	   * @brief The default constructor.
	   */
	  Mutex(void);

	  /**
	   * @brief The destructor.
	   */
	  ~Mutex(void);

	  /**
	   * @brief Lock the mutex.
	   *
	   * If the mutex is already locked, the caller thread is blocked
	   * until the mutex is free.
	   *
	   * @return false if the caller thread has already locked the mutex
	   * or if the mutex is invalid (bad initialization). Returns true
	   * if the mutex has successfuly been locked.
	   */
	  bool lock(void);

	  /**
	   * @brief Like Mutex::lock but non-blockant.
	   */
	  bool tryLock(void);

	  /**
	   * @brief Unlock the mutex.
	   *
	   * @return false if the mutex is invalid or already unlocked, otherwise true.
	   */
	  bool unlock(void);

	  friend class ConditionVariable<Trait>;

	private:
	  MutexHandle& getRawMutex(void);
      };

    template <typename Trait>
      Mutex<Trait>::Mutex(void)
      {
	this->_isInitialized = ThreadApi::createMutex(this->_handle);
      }

    template <typename Trait>
      Mutex<Trait>::~Mutex(void)
      {
	if (this->_isInitialized)
	  ThreadApi::destroyMutex(this->_handle);
      }

    template <typename Trait>
      inline bool Mutex<Trait>::lock(void)
      {
	return ThreadApi::lockMutex(this->_handle);
      }

    template <typename Trait>
      inline bool Mutex<Trait>::tryLock(void)
      {
	return ThreadApi::tryLockMutex(this->_handle);
      }

    template <typename Trait>
      inline bool Mutex<Trait>::unlock(void)
      {
	return ThreadApi::unlockMutex(this->_handle);
      }

    template <typename Trait>
      inline typename Mutex<Trait>::MutexHandle& Mutex<Trait>::getRawMutex(void)
      {
	return this->_handle;
      }
  } // namespace threads
} // namespace lblib
