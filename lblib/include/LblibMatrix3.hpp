#pragma once

#include <algorithm>

namespace lblib
{
  namespace math
  {
    /** @class Matrix3
     * @brief 3x3 matrices implementation.
     */
    template <typename T>
      class Matrix3
      {
	private:
	  T	_entries[9];

	  class Multiplier
	  {
	    private:
	      const T	_value;

	    public:
	      Multiplier(T value) :
		_value(value)
	      {
	      }

	      void operator () (T& value)
	      {
		value *= this->_value;
	      }
	  };

	  class Incrementer
	  {
	    private:
	      const T	_value;

	    public:
	      Incrementer(T value) :
		_value(value)
	      {
	      }

	      void operator () (T& value)
	      {
		value += this->_value;
	      }
	  };

	public:
	  Matrix3(T m1x1 = 0, T m1x2 = 0, T m1x3 = 0,
	      T m2x1 = 0, T m2x2 = 0, T m2x3 = 0,
	      T m3x1 = 0, T m3x2 = 0, T m3x3 = 0);
	  Matrix3(T entries[9]);
	  Matrix3(Matrix3 const& m);
	  ~Matrix3(void);

	public:
	  /*
	   * Operators :
	   */

	  Matrix3 const& operator = (Matrix3 const&);
	  Matrix3 operator - (void) const;

	  Matrix3<T> const& operator += (T value);
	  Matrix3<T> const& operator -= (T value);
	  Matrix3<T> const& operator *= (T value);
	  Matrix3<T> const& operator /= (T value);

	public:
	  /**
	   * @brief Sets the value of the entrie mij.
	   */
	  void set(unsigned int x, unsigned int y, T value);

	  T get(unsigned int x, unsigned int y) const;
      };

    template <typename T>
      Matrix3<T> operator +(Matrix3<T> const& mat, T value);
    template <typename T>
      Matrix3<T> operator -(Matrix3<T> const& mat, T value);
    template <typename T>
      Matrix3<T> operator *(Matrix3<T> const& mat, T value);
    template <typename T>
      Matrix3<T> operator /(Matrix3<T> const& mat, T value);

    template <typename T>
      Matrix3<T> operator + (Matrix3<T> const& a, Matrix3<T> const& b);
    template <typename T>
      Matrix3<T> operator * (Matrix3<T> const& a, Matrix3<T> const& b);

    typedef Matrix3<int>		Matrix3i;
    typedef Matrix3<unsigned int>	Matrix3ui;
    typedef Matrix3<float>		Matrix3f;
    typedef Matrix3<double>		Matrix3d;

    template <typename T>
      Matrix3<T>::Matrix3(T m1x1, T m1x2, T m1x3,
			T m2x1, T m2x2, T m2x3,
			T m3x1, T m3x2, T m3x3)
    {
	_entries[0] = m1x1;
	_entries[1] = m1x2;
	_entries[2] = m1x3;
	_entries[3] = m2x1;
	_entries[4] = m2x2;
	_entries[5] = m2x3;
	_entries[6] = m3x1;
	_entries[7] = m3x2;
	_entries[8] = m3x3;
    }

    template <typename T>
      Matrix3<T>::Matrix3(T entries[9])
      {
	std::copy(entries, entries + sizeof(entries),
	    this->entries);
      }

    template <typename T>
      Matrix3<T>::~Matrix3(void)
      {
      }

    template <typename T>
      inline Matrix3<T> const& Matrix3<T>::operator = (Matrix3<T> const& mat)
      {
	std::copy(mat._entries, mat._entries + sizeof(mat._entries),
	    this->_entries);
	return *this;
      }

    template <typename T>
      inline void Matrix3<T>::set (unsigned int x, unsigned int y, T value)
      {
	if ((x < 3) && (y < 3))
	  this->_entries[(y * 3) + x] = value;
      }

    template <typename T>
      inline T Matrix3<T>::get(unsigned int x, unsigned int y) const
      {
	if ((x < 3) && (y < 3))
	  return this->_entries[(y * 3) + x];
	else
	  return 0;
      }

    template <typename T>
      inline Matrix3<T> Matrix3<T>::operator -(void) const
      {
	return *this * -1;
      }

    template <typename T>
      inline Matrix3<T> operator + (Matrix3<T> const& mat, T value) 
      {
	Matrix3<T> matRes(mat);
	matRes += value;
	return matRes;
      }

    template <typename T>
      inline Matrix3<T> operator - (Matrix3<T> const& mat, T value)
      {
	Matrix3<T> matRes(mat);
	matRes -= value;
	return matRes;
      }

    template <typename T>
      inline Matrix3<T> operator * (Matrix3<T> const& mat, T value)
      {
	Matrix3<T> matRes(mat);
	matRes *= value;
	return matRes;
      }

    template <typename T>
      inline Matrix3<T> operator / (Matrix3<T> const& mat, T value)
      {
	Matrix3<T> matRes(mat);
	matRes /= value;
	return matRes;
      }

    template <typename T>
      inline Matrix3<T> const& Matrix3<T>::operator += (T value)
      {
	std::for_each(this->_entries, this->_entries + sizeof(this->_entries),
	    Matrix3<T>::Incrementer(value));
      }

    template <typename T>
      inline Matrix3<T> const& Matrix3<T>::operator -= (T value)
      {
	std::for_each(this->_entries, this->_entries + sizeof(this->_entries),
	    Matrix3<T>::Incrementer(-value));
      }

    template <typename T>
      inline Matrix3<T> const& Matrix3<T>::operator *= (T value)
      {
	std::for_each(this->_entries, this->_entries + sizeof(this->_entries),
	    Matrix3<T>::Multiplier(value));
      }

    template <typename T>
      inline Matrix3<T> const& Matrix3<T>::operator /= (T value)
      {
	std::for_each(this->_entries, this->_entries + sizeof(this->_entries),
	    Matrix3<T>::Multiplier(1 / value));
      }

    template <typename T>
      inline Matrix3<T> operator + (Matrix3<T> const& a, Matrix3<T> const& b)
      {
	Matrix3<T> m;

	for (unsigned int y = 0; y < 3; y++)
	{
	  for (unsigned int x = 0; x < 3; x++)
	    m.set(x, y, a.get(x, y) + b.get(x, y));
	}
	return m;
      }

    template <typename T>
      inline Matrix3<T> operator * (Matrix3<T> const& a, Matrix3<T> const& b)
      {
	Matrix3<T> m;

	for (unsigned int y = 0; y < 3; y++)
	{
	  for (unsigned int x = 0; x < 3; x++)
	  {
	    T value = 0;
	    for (unsigned int i = 0; i < 3; i++)
	      value += a.get(x + i, y) * b.get(x, y + i);
	    m.set(x, y, value);
	  }
	}
	return m;
      }
  } // namespace math
} // namespace lblib
