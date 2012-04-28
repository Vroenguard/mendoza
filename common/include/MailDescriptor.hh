//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	MailDescriptor.hh
// Creation:	Sat Apr 28 13:57:31 2012
//==============================================================================

#pragma once

#include <cstdlib>

namespace mail
{
  struct MailDescriptor
  {
    size_t	id;		///< The mail id.
    size_t	size;		///< Size in bytes.
    bool	toDelete;	///< Delete the mail in the update state ?
  }; // MailDescriptor
} // mail
