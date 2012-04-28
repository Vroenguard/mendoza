//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	FileLock.cpp
// Creation:	Sat Apr 28 13:40:17 2012
//==============================================================================

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "FileLock.hh"

namespace mail
{
  FileLock::FileLock(std::string const& name)
    : _fileName(name + ".lock")
  {
    _fd = open(_fileName.c_str(), O_CREAT | O_EXCL);
  }

  FileLock::~FileLock(void)
  {
    if (this->_fd != -1)
    {
      close(this->_fd);
    }
  }

  FileLock::operator bool(void)
  {
    if (this->_fd != -1)
    {
      return true;
    }
    return false;
  }
}
