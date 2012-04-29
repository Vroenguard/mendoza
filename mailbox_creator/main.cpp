//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	main.cpp
// Creation:	Sun Apr 29 12:22:06 2012
//==============================================================================

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "MailBox.hh"

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " login password\n";
    return EXIT_FAILURE;
  }
  mail::MailBox::Password password;
  strncpy(password, argv[2], sizeof(password));
  mail::MailBox mailBox(argv[1], "");
  mailBox.setPassword(password);
  mailBox.write();
  return EXIT_SUCCESS;
}
