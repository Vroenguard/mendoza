//==============================================================================
// @author:	antoine luciani <antoine1fr@gmail.com>
// File:	SmtpWorker.cpp
// Creation:	Sat Apr 28 22:07:49 2012
//==============================================================================

#include "SmtpWorker.hh"
#include "MailBox.hh"

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
#ifdef DEBUG
      std::cout << "[DEBUG] Worker thread: new client!! So excited!\n";
#endif // DEBUG
      this->_socket.setId(this->_queue.pop());
      this->_socket << "220 lucian_b.mendoza.epitech.eu. ESMTP mendoza"
	<< this->_eol;
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
      this->_nextAction = &SmtpWorker::_readCommand;
    }
    else if ((this->_line.find("quit") == 0)
	|| (this->_line.find("QUIT") == 0))
    {
      this->_socket << "221 2.0.0 Bye" << this->_eol;
      this->_socket.close();
    }
    else
    {
      this->_socket << "500 Unknown command" << this->_eol;
    }
  }

  void SmtpWorker::_readCommand(void)
  {
    size_t pos;
    if ((pos = this->_line.find("MAIL FROM: ")) == 0)
    {
      this->_nextAction = &SmtpWorker::_readMailRecipient;
      this->_socket << "250 2.1.0 Ok" << this->_eol;
    }
    else if ((this->_line.find("quit") == 0)
	|| (this->_line.find("QUIT") == 0))
    {
      this->_socket << "221 2.0.0 Bye" << this->_eol;
      this->_socket.close();
    }
    else
    {
      this->_socket << "500 Unknown command" << this->_eol;
    }
  }

  void SmtpWorker::_readMailRecipient(void)
  {
    size_t pos;
    std::string const command("RECPT TO: ");
    if ((pos = this->_line.find(command)) == 0)
    {
      this->_recipients.push_back(this->_line.substr(command.size(),
	    this->_line.rfind(this->_eol)));
      this->_socket << "250 2.1.0 Ok "
       << this->_recipients.back() << this->_eol;
    }
    else if ((pos = this->_line.find("DATA")) == 0)
    {
      this->_nextAction = &SmtpWorker::_readMailData;
      this->_mailDataState = 0;
      this->_mailData = "";
      this->_socket << "250 2.1.0 Ok" << this->_eol;
    }
    else
    {
      this->_socket << "500 Unknown command" << this->_eol;
    }
  }

  void SmtpWorker::_mailDataEndStage1(void)
  {
    if (this->_mailDataState == 0)
    {
      this->_mailDataState += 1;
    }
    else
    {
      this->_mailDataState = 0;
      this->_mailData += this->_line;
    }
  }

  void SmtpWorker::_readMailData(void)
  {
    if (this->_line == this->_eol)
    {
      this->_mailDataEndStage1();
    }
    else if ((this->_line == ".\r\n") && (this->_mailDataState == 1))
    {
      this->_saveMail();
      this->_socket << "250 2.1.0 Ok" << this->_eol;
      this->_nextAction = &SmtpWorker::_readCommand;
    }
    else
    {
      this->_mailData += this->_line;
    }
  }

  void SmtpWorker::_saveMail(void)
  {
    RecipientList::const_iterator it;
    for (it = this->_recipients.begin(); it != this->_recipients.end(); ++it)
    {
      mail::MailBox mailBox(it->substr(0, it->find_first_of('@')));
      mailBox.pushMail(this->_mailData);
    }
  }
} // smtp
