//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	MailBox.cpp
// Creation:	Sat Apr 28 14:03:52 2012
//==============================================================================

#include <fstream>
#include <sstream>

#include "MailBox.hh"
#include "FileLock.hh"

namespace mail
{
  MailBox::MailBox(std::string const& name)
    : _name(name)
  {
    std::string fileName(this->_name + ".mailbox");
    FileLock fileLock(fileName);
    update();
  }

  MailBox::MailBox(MailBox const& mailBox)
    : _name(mailBox._name), _size(mailBox._size), _exists(mailBox._exists),
    _mails(mailBox._mails)
  {
  }

  MailBox::~MailBox(void)
  {
  }

  MailBox const& MailBox::operator = (MailBox const& mailBox)
  {
    this->_name = mailBox._name;
    this->_size = mailBox._size;
    this->_exists = mailBox._exists;
    this->_mails = mailBox._mails;
    return *this;
  }

  void MailBox::update(void)
  {
    std::string fileName(this->_name + ".mailbox");
    std::ifstream file(fileName.c_str());

    if (file)
    {
      _exists = true;
      file.read(reinterpret_cast<char*>(&_maxId), sizeof(_maxId));
      file.seekg(0, std::ios_base::end);
      size_t fileSize = file.tellg();
      file.seekg(sizeof(_maxId), std::ios_base::beg);
      _mails.resize(fileSize / sizeof(MailDescriptor));
      file.read(reinterpret_cast<char*>(&_mails[0]), fileSize);
    }
    else
    {
      _exists = false;
    }
  }

  void MailBox::_writeDescriptors(void)
  {
    std::string fileName(this->_name + ".mailbox");
    std::ofstream mailBoxFile(fileName.c_str(),
	std::ios_base::out | std::ios_base::trunc);
    mailBoxFile.write(reinterpret_cast<char*>(&this->_maxId),
	sizeof(this->_maxId));
    mailBoxFile.write(reinterpret_cast<char*>(&this->_mails[0]),
	  sizeof(MailDescriptor) * this->_mails.size());
  }

  void MailBox::_writeMail(MailDescriptor const& descriptor,
      std::string const& content)
  {
    std::ostringstream strStream;
    strStream << this->_name << '.' << descriptor.id << ".mail";
    std::ofstream mailFile(strStream.str().c_str());
    mailFile.write(content.c_str(), content.length());
  }

  void MailBox::pushMail(std::string const& content)
  {
    FileLock fileLock(this->_name + ".mailbox");
    this->update();
    MailDescriptor descriptor;
    descriptor.id = ++this->_maxId;
    descriptor.size = content.size();
    descriptor.toDelete = false;
    this->_mails.push_back(descriptor);
    this->_writeDescriptors();
    this->_writeMail(descriptor, content);
  }

  bool MailBox::getMailContent(size_t id, std::string& content) const
  {
    std::ostringstream stream;
    stream << this->_name << '.' << id << ".mail";
    FileLock fileLock(stream.str());
    std::ifstream mailFile(stream.str().c_str());
    if (mailFile)
    {
      mailFile.seekg(0, std::ios_base::end);
      size_t size = mailFile.tellg();
      mailFile.seekg(0, std::ios_base::beg);
      content.resize(size);
      mailFile.read(&content[0], size);
      return true;
    }
    return false;
  }
} // mail
