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
#ifdef DEBUG
    std::cout << "[DEBUG] Worker thread: starting running.\n";
#endif // DEBUG
    while (42)
    {
      this->_condVar.wait();
      this->_socket.setId(this->_queue.pop());
      this->_nextAction = &SmtpWorker::_readHelo;
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

  void SmtpWorker::_readHelo(void)
  {
    if (this->_line.find("HELO ") == 0)
    {
      this->_socket
	<< "250 lucian_b.mendoza.epitech.eu. ESMTP Mendoza"
	<< this->_eol;
    }
    else if ((this->_line.find("quit") == 0)
	|| (this->_line.find("QUIT") == 0))
    {
      this->_socket << "221 2.0.0 Bye" << this->_eol;
      this->_socket.close();
    }
    else
    {
      this->_socket << "500 lucian_b.mendoza.epitech.eu. ESMTP Mendoza"
	<< this->_eol;
    }
  }
} // smtp
