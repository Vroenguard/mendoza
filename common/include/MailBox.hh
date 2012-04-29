//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	MailBox.hh
// Creation:	Sat Apr 28 14:00:06 2012
//==============================================================================

#pragma once

#include <cstdlib>
#include <string>
#include <vector>

#include "MailDescriptor.hh"

namespace mail
{
  class MailBox
  {
    public:
      enum
      {
	PASSWORD_LENGTH = 20,
	PASSWORD_SIZE
      };

      typedef char Password[PASSWORD_SIZE];

    private:
      typedef std::vector<MailDescriptor> MailList;

      std::string	_name; ///< Mail box' name.
      size_t		_size; ///< Total size the mails in bytes.
      size_t		_maxId;
      bool		_exists;
      MailList		_mails;
      std::string	_password;
      bool		_authenticated;
      Password		_realPassword;

    public:
      MailBox(std::string const& name, std::string const& password);
      MailBox(MailBox const& mailBox);
      ~MailBox(void);

      MailBox const& operator = (MailBox const&);
      void pushMail(std::string const& content);
      void update(void);
      bool getMailContent(size_t id, std::string& content) const;
      MailDescriptor const* getMailDescriptor(size_t id) const;
      bool deleteMail(size_t id);
      void write(void);
      operator bool (void);
      bool isAuthenticated(void);
      void setPassword(Password const&);

    private:
      void _writeDescriptors(void);
      void _writeMail(MailDescriptor const& descriptor,
	  std::string const& content);
  }; // MailBox
} // mail
