//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	main.cpp
// Creation:	Sun Apr 29 12:22:06 2012
//==============================================================================

#include <iostream>
#include <cstdlib>

#include "MailBox.hh"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " account_name\n";
    return EXIT_FAILURE;
  }
  mail::MailBox mailBox(argv[1], "");
  mailBox.write();
  return EXIT_SUCCESS;
}
