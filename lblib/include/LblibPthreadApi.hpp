#pragma once

#include "LblibCompilation.hh"
#ifdef LBLIB_PLATFORM_LINUX

# include <pthread.h>
# include <sys/types.h>
# include <signal.h>

namespace lblib
{
  namespace threads
  {
    template <typename Trait>
      class AThread;

    template <typename Trait>
      class PthreadApi
      {
	public:
	  typedef void (AThread<Trait>::*ThreadFunc)(void);

	private:
	  typedef typename Trait::Handle	Handle;
	  typedef typename Trait::MutexHandle	MutexHandle;
	  typedef typename Trait::CondHandle	CondHandle;

	  struct ThreadInfo
	  {
	    AThread<Trait>&	thread;
	    ThreadFunc		func;
	    pthread_cond_t&	cond;
	    pthread_mutex_t&	mutex;
	  };

	private:
	  PthreadApi(void);
	  PthreadApi(PthreadApi const&);

	  static void*	_launchThread(void* pdata);

	public:
	  static bool create(Handle& handle, AThread<Trait>& thread,
	      ThreadFunc threadFunc);

	  static bool join(Handle &handle);

	  static bool isValid(const Handle &handle);

	  static bool createMutex(MutexHandle& handle);

	  static bool destroyMutex(MutexHandle& handle);

	  static bool lockMutex(MutexHandle& handle);

	  static bool tryLockMutex(MutexHandle& handle);

	  static bool unlockMutex(MutexHandle& handle);

	  static bool cancelThread(Handle& handle);

	  static bool condVarInit(CondHandle& cond);
	  static bool condVarDestroy(CondHandle& cond);
	  static bool condVarSignal(CondHandle& cond);
	  static bool condVarBroadCast(CondHandle&);
	  static bool condVarWait(CondHandle&, MutexHandle&);
      };

    template <typename Trait>
      void* PthreadApi<Trait>::_launchThread(void* pdata)
      {
	ThreadInfo* info = reinterpret_cast<ThreadInfo*>(pdata);

	pthread_mutex_lock(&info->mutex);
	AThread<Trait>& thread = info->thread;
	ThreadFunc func = info->func;
	pthread_mutex_unlock(&info->mutex);
	pthread_cond_signal(&info->cond);

	(thread.*func)();
	return (NULL);
      }

    template <typename Trait>
      bool PthreadApi<Trait>::create(Handle& handle, AThread<Trait>& thread,
	  ThreadFunc threadFunc)
      {
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_mutex_lock(&mutex);
	ThreadInfo info = {thread, threadFunc, cond, mutex};

	if (pthread_create(&handle, NULL, &PthreadApi<Trait>::_launchThread,
	      &info) == -1)
	{
	  pthread_mutex_unlock(&mutex);
	  pthread_cond_destroy(&cond);
	  pthread_mutex_destroy(&mutex);
	  return (false);
	}
	else
	{
	  pthread_cond_wait(&cond, &mutex);
	  pthread_mutex_unlock(&mutex);
	  pthread_cond_destroy(&cond);
	  pthread_mutex_destroy(&mutex);
	  return (true);
	}
      }

    template <typename Trait>
      bool PthreadApi<Trait>::join(Handle &handle)
      {
	if (pthread_join(handle, NULL) != 0)
	  return (false);
	return (true);
      }

    template <typename Trait>
      bool PthreadApi<Trait>::isValid(const Handle &handle)
      {
	if (handle)
	  return true;
	return false;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::createMutex(MutexHandle& handle)
      {
	if (pthread_mutex_init(&handle, NULL) == -1)
	  return false;
	else
	  return true;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::destroyMutex(MutexHandle& handle)
      {
	if (pthread_mutex_destroy(&handle) == -1)
	  return false;
	else
	  return true;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::lockMutex(MutexHandle& handle)
      {
	if (pthread_mutex_lock(&handle) == -1)
	  return false;
	else
	  return true;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::tryLockMutex(MutexHandle& handle)
      {
	if (pthread_mutex_try_lock(&handle) == -1)
	  return false;
	else
	  return true;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::unlockMutex(MutexHandle& handle)
      {
	if (pthread_mutex_unlock(&handle) == -1)
	  return false;
	else
	  return true;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::cancelThread(Handle& handle)
      {
	if (pthread_cancel(handle) == 0)
	  return true;
	else
	  return false;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::condVarInit(CondHandle& cond)
      {
	if (pthread_cond_init(&cond, NULL) == 0)
	  return true;
	return false;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::condVarDestroy(CondHandle& cond)
      {
	if (pthread_cond_destroy(&cond) == 0)
	  return true;
	return false;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::condVarSignal(CondHandle& cond)
      {
	if (pthread_cond_signal(&cond) == 0)
	  return true;
	return false;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::condVarBroadCast(CondHandle& cond)
      {
	if (pthread_cond_broadcast(&cond) == 0)
	  return true;
	return false;
      }

    template <typename Trait>
      bool PthreadApi<Trait>::condVarWait(CondHandle& cond, MutexHandle& mutex)
      {
	if (pthread_cond_wait(&cond, &mutex) == 0)
	  return true;
	return false;
      }
  }
}

#endif // LBLIB_PLATFORM_LINUX
