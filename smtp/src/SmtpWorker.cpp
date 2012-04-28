//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	SmtpWorker.cpp
// Creation:	Sat Apr 28 22:07:49 2012
//==============================================================================

#include "SmtpWorker.hh"

namespace smtp
{
  SmtpWorker::SmtpWorker(threads::SafeQueue<int>& queue,
      threads::ConditionVariable<>& condVar)
    : _queue(queue), _condVar(condVar), _nextAction(NULL), _eol("\015\012")
  {
  }

  void SmtpWorker::run(void)
  {
    while (42)
    {
      this->_condVar.wait();
      this->_socket.setId(this->_queue.pop());
      this->_nextAction = &SmtpWorker::_readHelo;
      while (this->_socket)
      {
	this->_line = this->_socket.getLine();
	if (this->_nextAction)
	{
	  (this->*_nextAction)();
	}
      }
    }
  }

  void SmtpWorker::_readHelo(void)
  {
    if (this->_line.find("HELO ") == 0)
    {
      this->_socket
	<< std::string("250 lucian_b.mendoza.epitech.eu. ESMTP Mendoza")
	<< std::string("this->_eol");
    }
    else
    {
      this->_socket << "500 lucian_b.mendoza.epitech.eu. ESMTP Mendoza"
	<< this->_eol;
    }
  }
} // smtp
