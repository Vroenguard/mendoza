//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ClientSocket.cpp
// Creation:	Sat Apr 28 22:40:11 2012
//==============================================================================

#include <unistd.h>
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
} // net
