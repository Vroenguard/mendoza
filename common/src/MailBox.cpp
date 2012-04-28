//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	MailBox.cpp
// Creation:	Sat Apr 28 14:03:52 2012
//==============================================================================

#include <fstream>

#include "MailBox.hh"
#include "FileLock.hh"

namespace mail
{
  MailBox::MailBox(std::string const& name)
    : _name(name)
  {
    std::string fileName(name + ".mailbox");
    FileLock fileLock(fileName);
    std::ifstream file(fileName.c_str());

    if (file)
    {
      _exists = true;
      file.seekg(0, std::ios_base::end);
      size_t fileSize = file.tellg();
      file.seekg(0, std::ios_base::beg);
      _mails.resize(fileSize / sizeof(MailDescriptor));
      file.read(reinterpret_cast<char*>(&_mails[0]), fileSize);
    }
    else
    {
      _exists = false;
    }
  }

  MailBox::MailBox(MailBox const& mailBox)
    : _name(mailBox._name), _size(mailBox._size), _exists(mailBox._exists),
    _mails(mailBox._mails)
  {
  }
} // mail
