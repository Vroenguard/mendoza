//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ClientSocket.cpp
// Creation:	Sat Apr 28 22:40:11 2012
//==============================================================================

#include <unistd.h>
#include <cstring>

#include "ClientSocket.hh"

namespace net
{
  ClientSocket::ClientSocket(int id)
    : _id(id), _lineReady(false)
  {
  }

  ClientSocket::~ClientSocket(void)
  {
    this->close();
  }

  void ClientSocket::close(void)
  {
    if (this->_id != -1)
    {
      ::close(this->_id);
      this->_line = "";
      this->_lineReady = false;
    }
  }

  void ClientSocket::setId(int id)
  {
    this->close();
    this->_id = id;
  }

  ClientSocket::operator bool (void)
  {
    if (_id != -1)
    {
      return true;
    }
    return false;
  }

  std::string ClientSocket::getLine(void)
  {
    ssize_t readBytes;
    size_t pos;
    while ((pos = this->_line.find("\r\n")) == std::string::npos)
    {
      memset(this->_buffer, 0, sizeof(this->_buffer));
      readBytes = recv(this->_id, this->_buffer, sizeof(this->_buffer) - 1, 0);
      if ((readBytes == 0) || (readBytes == -1))
      {
	this->close();
	break;
      }
      this->_line += this->_buffer;
    }
    if (pos == std::string::npos)
    {
      std::string str = this->_line;
      this->_line = "";
      return str;
    }
    else
    {
      std::string str = this->_line.substr(0, pos + 2);
      this->_line.erase(pos);
      return str;
    }
  }
} // net
