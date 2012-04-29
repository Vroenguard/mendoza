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
#ifdef DEBUG
      std::cout << "[DEBUG] Worker thread: Greetings passed\n";
#endif // DEBUG
      this->_socket
	<< "250 lucian_b.mendoza.epitech.eu." << this->_eol;
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
    if ((pos = this->_line.find("MAIL FROM:")) == 0)
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
    std::string const command("RCPT TO:");
    if ((pos = this->_line.find(command)) == 0)
    {
      std::string rcpt(this->_line.substr(command.size(),
	    this->_line.rfind(this->_eol)));
      this->_epureRecipient(rcpt);
      this->_pushRecipient(rcpt);
    }
    else if ((pos = this->_line.find("DATA")) == 0)
    {
#ifdef DEBUG
      std::cout << "[DEBUG] 354 End data with <CR><LF>.<CR><LF>" << this->_eol;
#endif // DEBUG
      this->_nextAction = &SmtpWorker::_readMailData;
      this->_mailDataState = 0;
      this->_mailData = "";
      this->_socket << "354 ok\r\n";
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
#ifdef DEBUG
      std::cout << "[DEBUG] Concat to message: " << this->_line << '\n';
#endif // DEBUG
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
#ifdef DEBUG
      std::cout << "[DEBUG] 250 2.1.0 Ok" << this->_eol;
#endif // DEBUG
      this->_socket << "250 2.1.0 Ok" << this->_eol;
      this->_nextAction = &SmtpWorker::_readCommand;
    }
    else
    {
#ifdef DEBUG
      std::cout << "[DEBUG] Concat to message: " << this->_line << '\n';
#endif // DEBUG
      this->_mailData += this->_line;
    }
  }

  void SmtpWorker::_saveMail(void)
  {
    RecipientList::const_iterator it;
    for (it = this->_recipients.begin(); it != this->_recipients.end(); ++it)
    {
      mail::MailBox mailBox(it->substr(0, it->find_first_of('@')), "");
      if (mailBox)
      {
	mailBox.pushMail(this->_mailData);
      }
      else
      {
	this->_socket << "550 unknown mail box " << *it << this->_eol;
      }
    }
  }
  void SmtpWorker::_epureRecipient(std::string& rcpt)
  {
    while (rcpt.size() && ((rcpt[0] == ' ') || (rcpt[0] == '\t')
	|| (rcpt[0] == '<')))
    {
      rcpt.erase(0, 1);
#ifdef DEBUG
      std::cout << "Epuring RCPT: " << rcpt << '\n';
#endif
    }
    while (rcpt.size() && ((rcpt[rcpt.length() - 1] == ' ')
	|| (rcpt[rcpt.length() - 1] == '\t')
	|| (rcpt[rcpt.length() - 1] == '\n')
	|| (rcpt[rcpt.length() - 1] == '\r')
	|| (rcpt[rcpt.length() - 1] == '>')))
    {
      rcpt.erase(rcpt.length() - 1, 1);
#ifdef DEBUG
      std::cout << "Epuring RCPT: " << rcpt << '\n';
#endif
    }
  }

  void SmtpWorker::_pushRecipient(std::string const& rcpt)
  {
    std::string domain = rcpt.substr(rcpt.find_first_of('@') + 1);
    if (domain == "lucian-b.mendoza.epitech.eu")
    {
      this->_recipients.push_back(rcpt);
      this->_socket << "250 2.1.0 Ok "
	<< this->_recipients.back() << this->_eol;
    }
    else
    {
      this->_socket << "551 recipient not local" << this->_eol;
    }
  }
} // smtp
