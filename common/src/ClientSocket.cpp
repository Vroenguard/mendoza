//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ClientSocket.cpp
// Creation:	Sat Apr 28 22:40:11 2012
//==============================================================================

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

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
      this->_stream.str("");
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
    while (this->_stream.str().find("\r\n") == std::string::npos)
    {
      readBytes = recv(this->_id, this->_buffer, RECV_MAX_SIZE, 0);
      if ((readBytes == 0) || (readBytes == -1))
      {
	this->close();
	break;
      }
      this->_stream.write(this->_buffer, readBytes);
    }
    std::string str;
    std::getline(this->_stream, str);
    return str;
  }
} // net
