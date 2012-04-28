//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	FileLock.cpp
// Creation:	Sat Apr 28 13:40:17 2012
//==============================================================================

#include <fcntl.h>
#include <unistd.h>

#include "FileLock.hh"

namespace mail
{
  FileLock::FileLock(std::string const& name)
    : _fileName(name + ".lock")
  {
    do
    {
      usleep(20000);
      _fd = open(_fileName.c_str(), O_CREAT | O_EXCL);
    } while (_fd == -1);
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
