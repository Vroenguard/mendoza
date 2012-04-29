//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	Pop3Worker.hh
// Creation:	Sat Apr 28 22:00:19 2012
//==============================================================================

#pragma once

#include <list>
#include <map>

#include "LblibSafeQueue.hpp"
#include "LblibConditionVariable.hpp"

#include "IWorker.hh"
#include "ClientSocket.hh"
#include "MailBox.hh"

namespace threads = lblib::threads;

namespace pop3
{
  class Pop3Worker : public net::IWorker
  {
    private:
      typedef void (Pop3Worker::*Action)(void);
      typedef std::list<std::string> RecipientList;
      typedef void (Pop3Worker::*Command) (std::istringstream&);
      typedef std::map<std::string, Command> CommandMap;

      threads::SafeQueue<int>&		_queue;
      threads::ConditionVariable<>&	_condVar;
      Action				_nextAction;
      net::ClientSocket			_socket;
      std::string			_line;
      char const*			_eol;
      mail::MailBox*			_mailBox;
      CommandMap			_commands;

    public:
      Pop3Worker(threads::SafeQueue<int>& queue,
	  threads::ConditionVariable<>& condVar);
      virtual ~Pop3Worker(void);

    protected:
      virtual void run(void);

      Pop3Worker(Pop3Worker const&);
      Pop3Worker const& operator = (Pop3Worker const&);

    private:
      void _readIds(void);
      void _readCommand(void);
      void _statCommand(std::istringstream&);
      void _quitCommand(std::istringstream&);
  }; // Pop3Worker
} // pop3
