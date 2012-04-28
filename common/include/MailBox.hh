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
    private:
      std::string	_name; ///< Mail box' name.
      size_t		_size; ///< Total size the mails in bytes.
      size_t		_maxId;
      bool		_exists;

      typedef std::vector<MailDescriptor> MailList;
      MailList		_mails;

    public:
      MailBox(std::string const& name);
      MailBox(MailBox const& mailBox);
      ~MailBox(void);

      MailBox const& operator = (MailBox const&);
      void pushMail(std::string const& content);
      void update(void);

    private:
      void _writeDescriptors(void);
      void _writeMail(MailDescriptor const& descriptor,
	  std::string const& content);
  }; // MailBox
} // mail
