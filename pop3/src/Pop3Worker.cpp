//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	Pop3Worker.cpp
// Creation:	Sat Apr 28 22:07:49 2012
//==============================================================================

#include <sstream>
#include "Pop3Worker.hh"
#include "MailBox.hh"

namespace pop3
{
  Pop3Worker::Pop3Worker(threads::SafeQueue<int>& queue,
      threads::ConditionVariable<>& condVar)
    : _queue(queue), _condVar(condVar), _nextAction(NULL), _eol("\015\012"),
    _mailBox(NULL)
  {
  }

  Pop3Worker::~Pop3Worker(void)
  {
    if (this->_mailBox)
      delete this->_mailBox;
  }

  void Pop3Worker::run(void)
  {
#ifdef DEBUG
    std::cout << "[DEBUG] Worker thread: starting running.\n";
#endif // DEBUG
    while (42)
    {
      this->_condVar.wait();
#ifdef DEBUG
      std::cout << "[DEBUG] Worker thread: new client!! So excited!\n";
#endif // DEBUG
      this->_socket.setId(this->_queue.pop());
      this->_socket << "+OK POP3 server read" << this->_eol;
      this->_nextAction = &Pop3Worker::_readIds;
      while (this->_socket)
      {
	this->_line = this->_socket.getLine();
#ifdef DEBUG
	std::cout << "[DEBUG] Worker thread: line: " << this->_line << '\n';
#endif // DEBUG
	if (this->_nextAction)
	{
	  (this->*_nextAction)();
	}
      }
    }
  }

  void Pop3Worker::_readIds(void)
  {
    std::istringstream stream(this->_line);
    std::string command, login, password;
    stream >> command;
    if (command == "APOP")
    {
      stream >> login >> password;
      if (this->_mailBox)
	delete this->_mailBox;
      this->_mailBox = new mail::MailBox(login, password);
      if (*this->_mailBox && this->_mailBox->isAuthenticated())
      {
	this->_socket << "+OK" << this->_eol;
      }
      else
      {
	this->_socket << "-ERR bad login or password" << this->_eol;
      }
    }
    else if (command == "QUIT")
    {
      this->_nextAction = NULL;
      this->_socket
	<< "+OK lucian-b.mendoza.epitech.eu  POP3 server signing off"
	<< this->_eol;
      this->_socket.close();
    }
    else
    {
      this->_socket << "-ERR" << this->_eol;
    }
  }
} // pop3
