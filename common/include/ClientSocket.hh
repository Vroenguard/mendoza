//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ClientSocket.hh
// Creation:	Sat Apr 28 22:38:48 2012
//==============================================================================

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <sstream>

namespace net
{
  class ClientSocket
  {
    private:
      enum
      {
	RECV_MAX_SIZE = 512
      };

      int		_id;
      bool		_lineReady;
      char		_buffer[RECV_MAX_SIZE];
      std::string	_line;

    public:
      ClientSocket(int id = -1);
      ~ClientSocket(void);

      void close(void);
      void setId(int id);
      operator bool ();
      std::string getLine(void);
      template <typename T>
	ClientSocket& operator << (T const& value)
	{
	  std::ostringstream stream;
	  stream << value;
	  send(this->_id, stream.str().c_str(), stream.str().length(), 0);
	  return *this;
	}

    private:
      ClientSocket(ClientSocket const&);
      ClientSocket const& operator = (ClientSocket const&);
  };
} // net
