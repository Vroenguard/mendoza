//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	Pop3Worker.cpp
// Creation:	Sat Apr 28 22:07:49 2012
//==============================================================================

#include "Pop3Worker.hh"
#include "MailBox.hh"

namespace pop3
{
  Pop3Worker::Pop3Worker(threads::SafeQueue<int>& queue,
      threads::ConditionVariable<>& condVar)
    : _queue(queue), _condVar(condVar), _nextAction(NULL), _eol("\015\012")
  {
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
      this->_socket << "220 lucian_b.mendoza.epitech.eu. ESMTP mendoza"
	<< this->_eol;
      this->_nextAction = NULL;
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
} // pop3
