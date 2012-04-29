//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	main.cpp
// Creation:	Sat Apr 28 21:02:04 2012
//==============================================================================

#include "Pop3Server.hh"

int main(void)
{
  pop3::Pop3Server server;
  return server.run();
}
