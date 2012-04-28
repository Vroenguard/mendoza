
#pragma once

#ifndef _WIN32

#include <unistd.h>

#include "LblibLinuxProcessApi.hpp"

namespace lblib
{
  namespace threads
  {
    class LinuxProcessTrait
    {
    private:
      LinuxProcessTrait(void);
      LinuxProcessTrait(const LinuxProcessTrait&);

    public:
      typedef pid_t					Handle;
      typedef LinuxProcessApi<LinuxProcessTrait>	Api;
    };

    typedef LinuxProcessTrait DefaultProcessTrait;
  } // namespace threads
} // namespace lblib

#endif // !_WIN32
