//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	FileLock.hh
// Creation:	Sat Apr 28 13:36:01 2012
//==============================================================================

#pragma once

#include <string>

namespace mail
{
  class FileLock
  {
    private:
      int		_fd;
      std::string	_fileName;

      FileLock(FileLock const&);
      FileLock const& operator = (FileLock const&);

    public:
      FileLock(std::string const& name);
      ~FileLock(void);
      operator bool (void);
  }; // FileLock
} // mail
