#pragma once

#include <queue>

#include "LblibMutex.hpp"
#include "LblibScopedLock.hpp"

namespace lblib
{
  namespace threads
  {
    /// @brief Thread safe std::queue encapsulation.
    template <typename T>
      class SafeQueue
      {
	private:
	  typedef std::queue<T>	RawQueue;
	  Mutex<>	_mutex;
	  RawQueue	_rawQueue;

	public:
	  /// @brief Default constructor.
	  SafeQueue(void);

	  /// @brief Copy constructor.
	  SafeQueue(SafeQueue const&);

	  /// @brief The destructor.
	  ~SafeQueue(void);

	  /// @brief Affectation operator.
	  SafeQueue<T> const& operator = (SafeQueue<T> const&);

	  /// @brief std::queue<>::push equivalent
	  void push(T const&);

	  /**
	   * @brief Remove the first value off the stack.
	   * @return The value.
	   */
	  T pop(void);
      };

    template <typename T>
      SafeQueue<T>::SafeQueue(void)
      {
      }

    template <typename T>
      SafeQueue<T>::SafeQueue(SafeQueue const& queue)
      {
	ScopedLock<> lock(queue._mutex);
	this->_rawQueue = queue._rawQueue;
      }

    template <typename T>
      SafeQueue<T>::~SafeQueue(void)
      {
      }

    template <typename T>
      SafeQueue<T> const&
      SafeQueue<T>::operator = (SafeQueue<T> const& queue)
      {
	ScopedLock<> thisLock(this->_mutex);
	ScopedLock<> queueLock(queue._mutex);
	this->_rawQueue = queue._rawQueue;
	return *this;
      }

    template <typename T>
      void SafeQueue<T>::push(T const& value)
      {
	ScopedLock<> lock(this->_mutex);
	this->_rawQueue.push(value);
      }

    template <typename T>
      T SafeQueue<T>::pop(void)
      {
	ScopedLock<> lock(this->_mutex);
	T value(this->_rawQueue.front());
	this->_rawQueue.pop();
	return value;
      }
  } // threads
} // lblib
