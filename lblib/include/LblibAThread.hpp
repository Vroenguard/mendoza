#pragma once
#include <iostream>

#include "LblibLinuxTrait.hh"

namespace lblib
{
  namespace threads
  {
    /** @class AThread
     * @brief Abstract class for threads handling.
     */
    template <typename Trait>
      class AThread
      {
	private:
	  typedef typename Trait::Handle	Handle;
	  typedef typename Trait::Api		Api;

	private:
	  Handle		_handle;

	public:
	  /**
	   * @brief Default constructor.
	   *
	   * Doesn't launch the thread (@see AThread::launch).
	   */
	  AThread(void);

	  /**
	   * @brief Copy constructor.
	   */
	  AThread(AThread const&);

	  /**
	   * @brief The destructor.
	   */
	  virtual ~AThread(void);

	  /**
	   * @brief Allows a thread to wait for another thread to end.
	   *
	   * If join fails, the reason is printed on the error output.
	   *
	   * @return false if join fail (already waiting, or thread tries to
	   * wait for himself. Returns true on success.
	   */
	  virtual bool		join(void);

	  /**
	   * @brief Launches the thread.
	   */
	  virtual bool		launch(void);

	  /**
	   * @brief Kills the thread immediately.
	   */
	  virtual bool		cancel(void);

	private:
	  // A thread interface can't be reaffected.
	  AThread<Trait> const& operator = (AThread<Trait> const&);

	protected:
	  virtual void		run(void) = 0;
      };

    typedef AThread<DefaultTrait::ThreadTrait>	Thread;

    template <typename Trait>
    AThread<Trait>::AThread(void) :
      _handle(0)
    {
    }

    template <typename Trait>
    AThread<Trait>::AThread(const AThread<Trait> &other) :
      _handle(other._handle)
    {
    }

    template <typename Trait>
      AThread<Trait>::~AThread(void)
      {
      }

    template <typename Trait>
      bool AThread<Trait>::launch(void)
      {
	Api::create(this->_handle, *this, &AThread<Trait>::run);
	if (Api::isValid(this->_handle))
	  return (true);
	else
	  return (false);
      }

    template <typename Trait>
      bool AThread<Trait>::join(void)
      {
	if (Api::isValid(this->_handle))
	  return Api::join(this->_handle);
	else
	  return (false);
      }

    template <typename Trait>
      bool AThread<Trait>::cancel(void)
      {
	return Api::cancelThread(this->_handle);
      }
  } // namespace threads
} // namespace lblib
