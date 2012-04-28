#ifndef SHAREDPTR_HPP_
# define SHAREDPTR_HPP_

# include <stdexcept>

namespace lblib
{
/**
 * @brief Implementation of shared pointers.
 *
 * It manages raw c-style pointers so once instanced, please use only the
 * shared pointer to manipulate your data AND your pointer.
 *
 * Shared pointers rely on reference counting. Every shared pointers managing
 * the same raw pointer have a pointer on the same reference count.
 * The first instance of SharedPtr using a given raw pointer creates the
 * reference count. The last instance deletes the reference count and the
 * data pointed by the raw pointer.
 *
 * A shared pointer behaves like a raw pointer. It can be :
 * - set to NULL
 * - reaffected
 * - dereferenced using the unary operator *
 *
 * Data can be accessed using the operator -> .
 */
  template <typename T>
  class SharedPtr
  {
  private:
    unsigned int*		_refCount;
    T**			_rawPtr;

  public:
    /**
     * @brief The default constructor.
     *
     * @param rawPtr : the real pointer to the data. It can be null.
     */
    SharedPtr(T* rawPtr = 0);

    /**
     * @brief The copy constructor.
     *
     * Adds one reference to the reference count and copy the raw pointer.
     */
    SharedPtr(SharedPtr const&);

    /**
     * @brief The destructor.
     */
    ~SharedPtr(void);

  public:
    SharedPtr const&	operator = (SharedPtr const&);
    SharedPtr const&	operator = (T* rawPtr);
    T&			operator * (void);
    T const&		operator * (void) const;
    T*			operator -> (void);
    T const*		operator -> (void) const;
			operator bool (void) const;
    bool		operator ! (void) const;

  private:
    void		_release(void);
  };

  template <typename T>
  SharedPtr<T>::SharedPtr(T* rawPtr) :
    _refCount(new unsigned int(1)), _rawPtr(new T*(rawPtr))
  {
  }

  template <typename T>
  SharedPtr<T>::SharedPtr(SharedPtr const& ptr) :
    _refCount(ptr._refCount), _rawPtr(ptr._rawPtr)
  {
    *this->_refCount += 1;
  }

  template <typename T>
  SharedPtr<T>::~SharedPtr(void)
  {
    this->_release();
  }

  template <typename T>
  SharedPtr<T> const& SharedPtr<T>::operator = (SharedPtr const& ptr)
  {
    this->_release();
    this->_refCount = ptr._refCount;
    this->_rawPtr = ptr._rawPtr;
    *this->_refCount += 1;

    return *this;
  }

  template <typename T>
  SharedPtr<T> const& SharedPtr<T>::operator = (T* rawPtr)
  {
    this->_release();
    this->_refCount = new unsigned int(1);
    this->_rawPtr = new T*(rawPtr);
    return *this;
  }

  template <typename T>
  T const& SharedPtr<T>::operator * (void) const
  {
    if (*this->_rawPtr)
      return **(this->_rawPtr);
    else
      throw std::runtime_error("Tried to dereference a null pointer.");
  }

  template <typename T>
  T& SharedPtr<T>::operator * (void)
  {
    if (*this->_rawPtr)
      return **(this->_rawPtr);
    else
      throw std::runtime_error("Tried to dereference a null pointer.");
  }

  template <typename T>
  void SharedPtr<T>::_release(void)
  {
    if (this->_refCount && this->_rawPtr)
    {
      *this->_refCount -= 1;
      if (*this->_refCount == 0)
      {
	if (*this->_rawPtr)
	  delete *this->_rawPtr;
	delete this->_rawPtr;
	delete this->_refCount;

	this->_rawPtr = 0;
	this->_refCount = 0;
      }
    }
  }

  template <typename T>
  T* SharedPtr<T>::operator -> (void)
  {
    return *this->_rawPtr;
  }

  template <typename T>
  T const* SharedPtr<T>::operator -> (void) const
  {
    return *this->_rawPtr;
  }

  template <typename T>
    inline SharedPtr<T>::operator bool (void) const
    {
      if (this->_rawPtr && *this->_rawPtr)
	return true;
      return false;
    }

  template <typename T>
    inline bool SharedPtr<T>::operator ! (void) const
    {
      if (this->_rawPtr && *this->_rawPtr)
	return false;
      return true;
    }
} // namespace lblib

#endif // !SHAREDPTR_HPP_
