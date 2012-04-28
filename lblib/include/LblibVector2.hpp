#pragma once

#include <iostream>

namespace lblib
{
  namespace math
  {
    template <typename T>
      class Vector2
      {
	private:
	  T	_x;
	  T	_y;

	public:
	  Vector2(T x = 0, T y = 0);
	  Vector2(Vector2<T> const& v);
	  ~Vector2(void);

	public:
	  Vector2<T> const& operator = (Vector2<T> const& v);
	  Vector2<T> const& operator = (T value);

	  Vector2<T> const& operator += (Vector2<T> const& v);
	  Vector2<T> const& operator -= (Vector2<T> const& v);

	  Vector2<T> const& operator += (T value);
	  Vector2<T> const& operator -= (T value);
	  Vector2<T> const& operator *= (T value);
	  Vector2<T> const& operator /= (T value);

	public:
	  T		getX(void) const;
	  T		getY(void) const;

	  void		setX(T x);
	  void		setY(T y);
	  void		set(T x, T y);

	public:
	  double		length(void) const;
	  double		dot(Vector2<T> const& v) const;
	  void		normalize(void);
      };

    template <typename T>
      Vector2<T>	operator + (Vector2<T> const& v1, Vector2<T> const& v2);
    template <typename T>
      Vector2<T>	operator - (Vector2<T> const& v1, Vector2<T> const& v2);

    template <typename T>
      Vector2<T>	operator + (Vector2<T> const& v, T value);
    template <typename T>
      Vector2<T>	operator - (Vector2<T> const& v, T value);
    template <typename T>
      Vector2<T>	operator * (Vector2<T> const& v, T value);
    template <typename T>
      Vector2<T>	operator / (Vector2<T> const& v, T value);

    template <typename T>
      bool	operator == (Vector2<T> const& u, Vector2<T> const& v);
    template <typename T>
      bool	operator != (Vector2<T> const& u, Vector2<T> const& v);

    typedef Vector2<float>	Vector2f;
    typedef Vector2<int>		Vector2i;
    typedef Vector2<unsigned int>	Vector2ui;
    typedef Vector2<double>	Vector2d;

    template <typename T>
      Vector2<T>::Vector2(T x, T y) :
	_x(x), _y(y)
    {
    }

    template <typename T>
      Vector2<T>::Vector2(Vector2<T> const& v) :
	_x(v._x), _y(v._y)
    {
    }

    template <typename T>
      Vector2<T>::~Vector2(void)
      {
      }

    template <typename T>
      Vector2<T> const& Vector2<T>::operator = (Vector2<T> const& v)
      {
	this->_x = v._x;
	this->_y = v._y;
	return *this;
      }

    template <typename T>
      Vector2<T> const& Vector2<T>::operator = (T value)
      {
	this->_x = value;
	this->_y = value;
	return *this;
      }

    template <typename T>
      T Vector2<T>::getX(void) const
      {
	return this->_x;
      }

    template <typename T>
      T Vector2<T>::getY(void) const
      {
	return this->_y;
      }

    template <typename T>
      void Vector2<T>::setX(T x)
      {
	this->_x = x;
      }

    template <typename T>
      void Vector2<T>::setY(T y)
      {
	this->_y = y;
      }

    template <typename T>
      void Vector2<T>::set(T x, T y)
      {
	this->_x = x;
	this->_y = y;
      }

    template <typename T>
      Vector2<T> const& Vector2<T>::operator += (Vector2<T> const& v)
      {
	this->_x += v._x;
	this->_y += v._y;
	return *this;
      }

    template <typename T>
      Vector2<T> const& Vector2<T>::operator -= (Vector2<T> const& v)
      {
	this->_x -= v._x;
	this->_y -= v._y;
	return *this;
      }

    template <typename T>
      Vector2<T> const& Vector2<T>::operator += (T value)
      {
	this->_x += value;
	this->_y += value;
	return *this;
      }

    template <typename T>
      Vector2<T> const& Vector2<T>::operator -= (T value)
      {
	this->_x -= value;
	this->_y -= value;
	return *this;
      }

    template <typename T>
      Vector2<T> const& Vector2<T>::operator *= (T value)
      {
	this->_x *= value;
	this->_y *= value;
	return *this;
      }

    template <typename T>
      Vector2<T> const& Vector2<T>::operator /= (T value)
      {
	this->_x /= value;
	this->_y /= value;
	return *this;
      }

    template <typename T>
      double Vector2<T>::length(void) const
      {
	return sqrt((this->_x * this->_x) + (this->_y * this->_y));
      }

    template <typename T>
      double Vector2<T>::dot(Vector2<T> const& v) const
      {
	return ((this->_x * v._x) + (this->_y * v._y));
      }

    template <typename T>
      void Vector2<T>::normalize(void)
      {
	*this /= this->length();
      }

    template <typename T>
      Vector2<T> operator + (Vector2<T> const& v1, Vector2<T> const& v2)
      {
	Vector2<T> v(v1);
	v += v2;
	return v;
      }

    template <typename T>
      Vector2<T> operator - (Vector2<T> const& v1, Vector2<T> const& v2)
      {
	Vector2<T> v(v1);
	v -= v2;
	return v;
      }

    template <typename T>
      Vector2<T> operator + (Vector2<T> const& v, T value)
      {
	Vector2<T> vRes(v);
	vRes += value;
	return vRes;
      }

    template <typename T>
      Vector2<T> operator - (Vector2<T> const& v, T value)
      {
	Vector2<T> vRes(v);
	vRes -= value;
	return vRes;
      }

    template <typename T>
      Vector2<T> operator * (Vector2<T> const& v, T value)
      {
	Vector2<T> vRes(v);
	vRes *= value;
	return vRes;
      }

    template <typename T>
      Vector2<T> operator / (Vector2<T> const& v, T value)
      {
	Vector2<T> vRes(v);
	vRes /= value;
	return vRes;
      }

    template <typename T>
      bool operator == (Vector2<T> const& u, Vector2<T> const& v)
      {
	if ((u.getX() == v.getX()) && (u.getY() == v.getY()))
	  return true;
	return false;
      }

    template <typename T>
      bool operator != (Vector2<T> const& u, Vector2<T> const& v)
      {
	if (u == v)
	  return false;
	return true;
      }

    template <typename T>
      std::ostream& operator << (std::ostream& out, Vector2<T> const& v)
      {
	out << "v2(" << v.getX() << ", " << v.getY() << ')';
	return out;
      }
  }
}
