//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	ClientSocket.hh
// Creation:	Sat Apr 28 22:38:48 2012
//==============================================================================

#pragma once

#include <sstream>

namespace net
{
  class ClientSocket
  {
    private:
      int		_id;
      bool		_lineReady;
      std::stringstream	_stream;

      enum
      {
	RECV_MAX_SIZE = 512
      };

    public:
      ClientSocket(int id = -1);
      ~ClientSocket(void);

      void close(void);

    private:
      ClientSocket(ClientSocket const&);
      ClientSocket const& operator = (ClientSocket const&);
  };
} // net
