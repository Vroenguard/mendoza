//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	SmtpWorker.hh
// Creation:	Sat Apr 28 22:00:19 2012
//==============================================================================

#pragma once

#include <list>

#include "LblibSafeQueue.hpp"
#include "LblibConditionVariable.hpp"

#include "IWorker.hh"
#include "ClientSocket.hh"

namespace threads = lblib::threads;

namespace smtp
{
  class SmtpWorker : public net::IWorker
  {
    private:
      typedef void (SmtpWorker::*Action)(void);
      typedef std::list<std::string> RecipientList;

      threads::SafeQueue<int>&		_queue;
      threads::ConditionVariable<>&	_condVar;
      Action				_nextAction;
      net::ClientSocket			_socket;
      std::string			_line;
      char const*			_eol;
      RecipientList			_recipients;
      int				_mailDataState;
      std::string			_mailData;

    public:
      SmtpWorker(threads::SafeQueue<int>& queue,
	  threads::ConditionVariable<>& condVar);

    protected:
      virtual void run(void);

      SmtpWorker(SmtpWorker const&);
      SmtpWorker const& operator = (SmtpWorker const&);

    private:
      void _readHelo(void);
      void _readCommand(void);
      void _readMailRecipient(void);
      void _readMailData(void);
      void _mailDataEndStage1(void);
      void _saveMail(void);
      void _epureRecipient(std::string& rcpt);
      void _pushRecipient(std::string const& rcpt);
  }; // SmtpWorker
} // smtp
