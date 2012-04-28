
#pragma once

#ifndef _WIN32

#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

namespace lblib
{
  namespace threads
  {
    template <typename Trait>
    class AThread;

    template <typename Trait>
    class LinuxProcessApi
    {
    public:
      typedef void	(AThread<Trait>::*ProcessFunc)(void);

    private:
      typedef typename Trait::Handle	Handle;

      struct ProcessInfo
      {
	AThread<Trait>		&process;
	ProcessFunc		func;
      };

    private:
      LinuxProcessApi(void);
      LinuxProcessApi(const LinuxProcessApi&);

      static void	_launchProcess(ProcessInfo *info);

    public:
      static bool	create(Handle &handle, AThread<Trait> &process,
			       ProcessFunc processFunc);
      static bool	join(Handle &handle);
      static bool	isValid(const Handle &handle);
      static bool	cancelThread(Handle& handle);
    };

    template <typename Trait>
    bool	LinuxProcessApi<Trait>::create(LinuxProcessApi<Trait>::Handle &handle,
					       AThread<Trait> &process,
					       LinuxProcessApi<Trait>::ProcessFunc func)
    {
      ProcessInfo info = {process, func};

      handle = fork();
      if (!handle)
	LinuxProcessApi<Trait>::_launchProcess(&info);
      else if (handle > 0)
	return true;
      return false;
    }

    template <typename Trait>
    bool	LinuxProcessApi<Trait>::join(LinuxProcessApi<Trait>::Handle &handle)
    {
      if (waitpid(handle, NULL, 0) < 0)
	return false;
      return true;
    }

    template <typename Trait>
    bool	LinuxProcessApi<Trait>::isValid(const LinuxProcessApi<Trait>::Handle &handle)
    {
      if (handle < 0)
	return false;
      return true;
    }

    template <typename Trait>
    void	LinuxProcessApi<Trait>::_launchProcess(LinuxProcessApi<Trait>::ProcessInfo *info)
    {
      AThread<Trait> &process = info->process;
      ProcessFunc func = info->func;

      (process.*func)();
      exit(EXIT_SUCCESS);
    }

    template <typename Trait>
      bool LinuxProcessApi<Trait>::cancelThread(Handle& handle)
      {
	if (kill(handle, SIGTERM) == -1)
	  return false;
	else
	  return true;
      }

  } // namespace threads
} // namespace lblib

#endif // !_WIN32
