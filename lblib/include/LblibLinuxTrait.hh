#pragma once
#ifndef _WIN32

# include "LblibPthreadTrait.hh"

namespace lblib
{
  class LinuxTrait
  {
    private:
      LinuxTrait(void);
      LinuxTrait(LinuxTrait const&);

    public:
      typedef threads::PthreadTrait		ThreadTrait;
  };

  typedef LinuxTrait DefaultTrait;
} // namespace lblib

#endif // !_WIN32
