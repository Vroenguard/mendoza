#pragma once

#include <iostream>

namespace lblib
{
  namespace math
  {
    template <typename T>
      class Vector3
      {
	private:
	  T	_x;
	  T	_y;
	  T	_z;

	public:
	  Vector3(T x = 0, T y = 0, T z = 0);
	  Vector3(Vector3<T> const& v);
	  ~Vector3(void);

	public:
	  Vector3<T> const& operator = (Vector3<T> const& v);
	  Vector3<T> const& operator = (T value);

	  Vector3<T> const& operator += (Vector3<T> const& v);
	  Vector3<T> const& operator -= (Vector3<T> const& v);

	  Vector3<T> const& operator += (T value);
	  Vector3<T> const& operator -= (T value);
	  Vector3<T> const& operator *= (T value);
	  Vector3<T> const& operator /= (T value);

	public:
	  T		getX(void) const;
	  T		getY(void) const;
	  T		getZ(void) const;

	  void		setX(T x);
	  void		setY(T y);
	  void		setZ(T z);
	  void		set(T x = 0, T y = 0, T z = 0);

	public:
	  double		length(void) const;
	  double		dot(Vector3<T> const& v) const;
	  Vector3<T>	cross(Vector3<T> const& v) const;
	  void		normalize(void);
      };

    template <typename T>
      Vector3<T> operator + (Vector3<T> const& v1, Vector3<T> const& v2);
    template <typename T>
      Vector3<T> operator - (Vector3<T> const& v1, Vector3<T> const& v2);

    template <typename T>
      Vector3<T> operator + (Vector3<T> const& v, T value);
    template <typename T>
      Vector3<T> operator - (Vector3<T> const& v, T value);
    template <typename T>
      Vector3<T> operator * (Vector3<T> const& v, T value);
    template <typename T>
      Vector3<T> operator / (Vector3<T> const& v, T value);

    template <typename T>
      bool	operator == (Vector3<T> const& u, Vector3<T> const& v);
    template <typename T>
      bool	operator != (Vector3<T> const& u, Vector3<T> const& v);

    typedef Vector3<float>	Vector3f;
    typedef Vector3<int>		Vector3i;
    typedef Vector3<unsigned int>	Vector3ui;
    typedef Vector3<double>	Vector3d;

    template <typename T>
      Vector3<T>::Vector3(T x, T y, T z) :
	_x(x), _y(y), _z(z)
    {
    }

    template <typename T>
      Vector3<T>::Vector3(Vector3<T> const& v) :
	_x(v._x), _y(v._y), _z(v._z)
    {
    }

    template <typename T>
      Vector3<T>::~Vector3(void)
      {
      }

    template <typename T>
      Vector3<T> const& Vector3<T>::operator = (Vector3<T> const& v)
      {
	this->_x = v._x;
	this->_y = v._y;
	this->_z = v._z;
	return *this;
      }

    template <typename T>
      Vector3<T> const& Vector3<T>::operator = (T value)
      {
	this->_x = value;
	this->_y = value;
	this->_z = value;
	return *this;
      }

    template <typename T>
      T Vector3<T>::getX(void) const
      {
	return this->_x;
      }

    template <typename T>
      T Vector3<T>::getY(void) const
      {
	return this->_y;
      }

    template <typename T>
      T Vector3<T>::getZ(void) const
      {
	return this->_z;
      }

    template <typename T>
      void Vector3<T>::setX(T x)
      {
	this->_x = x;
      }

    template <typename T>
      void Vector3<T>::setY(T y)
      {
	this->_y = y;
      }

    template <typename T>
      void Vector3<T>::setZ(T z)
      {
	this->_z = z;
      }

    template <typename T>
      void Vector3<T>::set(T x, T y, T z)
      {
	this->_x = x;
	this->_y = y;
	this->_z = z;
      }

    template <typename T>
      Vector3<T> const& Vector3<T>::operator += (Vector3<T> const& v)
      {
	this->_x += v._x;
	this->_y += v._y;
	this->_z += v._z;
	return *this;
      }

    template <typename T>
      Vector3<T> const& Vector3<T>::operator -= (Vector3<T> const& v)
      {
	this->_x -= v._x;
	this->_y -= v._y;
	this->_z -= v._z;
	return *this;
      }

    template <typename T>
      Vector3<T> const& Vector3<T>::operator += (T value)
      {
	this->_x += value;
	this->_y += value;
	this->_z += value;
	return *this;
      }

    template <typename T>
      Vector3<T> const& Vector3<T>::operator -= (T value)
      {
	this->_x -= value;
	this->_y -= value;
	this->_z -= value;
	return *this;
      }

    template <typename T>
      Vector3<T> const& Vector3<T>::operator *= (T value)
      {
	this->_x *= value;
	this->_y *= value;
	this->_z *= value;
	return *this;
      }

    template <typename T>
      Vector3<T> const& Vector3<T>::operator /= (T value)
      {
	this->_x /= value;
	this->_y /= value;
	this->_z /= value;
	return *this;
      }

    template <typename T>
      double Vector3<T>::length(void) const
      {
	return sqrt((this->_x * this->_x) + (this->_y * this->_y)
	    + (this->_z * this->_z));
      }

    template <typename T>
      double Vector3<T>::dot(Vector3<T> const& v) const
      {
	return ((this->_x * v._x) + (this->_y * v._y) + (this->_z * v._z));
      }

    template <typename T>
      Vector3<T> Vector3<T>::cross(Vector3<T> const& v) const
      {
	return Vector3<T>((this->_y * v._z) - (this->_z * v._y),
	    (this->_z * v._x) - (this->_x * v._z),
	    (this->_x * v._y) - (this->_y * v._x));
      }

    template <typename T>
      void Vector3<T>::normalize(void)
      {
	*this /= this->length();
      }

    template <typename T>
      Vector3<T> operator + (Vector3<T> const& v1, Vector3<T> const& v2)
      {
	Vector3<T> v(v1);
	v += v2;
	return v;
      }

    template <typename T>
      Vector3<T> operator - (Vector3<T> const& v1, Vector3<T> const& v2)
      {
	Vector3<T> v(v1);
	v -= v2;
	return v;
      }

    template <typename T>
      Vector3<T> operator + (Vector3<T> const& v, T value)
      {
	Vector3<T> vRes(v);
	vRes += value;
	return vRes;
      }

    template <typename T>
      Vector3<T> operator - (Vector3<T> const& v, T value)
      {
	Vector3<T> vRes(v);
	vRes -= value;
	return vRes;
      }

    template <typename T>
      Vector3<T> operator * (Vector3<T> const& v, T value)
      {
	Vector3<T> vRes(v);
	vRes *= value;
	return vRes;
      }

    template <typename T>
      Vector3<T> operator / (Vector3<T> const& v, T value)
      {
	Vector3<T> vRes(v);
	vRes /= value;
	return vRes;
      }

    template <typename T>
      bool operator == (Vector3<T> const& u, Vector3<T> const& v)
      {
	if ((u.getX() == v.getX()) && (u.getY() == v.getY())
	    && (u.getZ() == v.getZ()))
	  return true;
	return false;
      }

    template <typename T>
      bool operator != (Vector3<T> const& u, Vector3<T> const& v)
      {
	if (u == v)
	  return false;
	return true;
      }

    template <typename T>
      std::ostream& operator << (std::ostream& out, Vector3<T> const& v)
      {
	out << "v3(" << v.getX() << ", " << v.getY() << ", "
	  << v.getZ() << ')';
	return out;
      }
  }
}

