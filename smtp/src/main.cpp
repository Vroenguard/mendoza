//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	main.cpp
// Creation:	Sat Apr 28 21:02:04 2012
//==============================================================================

#include "SmtpServer.hh"

int main(void)
{
  smtp::SmtpServer server;
  return server.run();
}
