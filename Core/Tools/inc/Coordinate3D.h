#ifndef COORDINATE3D_H_
#define COORDINATE3D_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Coordinate3D.h
//! @brief  Definition of Coordinate3D<T> template
//! @author Scientific Computing Group at FRM II
//! @date   Jul 13, 2012

#include <cmath>

#include <gsl/gsl_sf_trig.h>

template <class T> class Coordinate3D
{
public:
    Coordinate3D(T x, T y, T z)
    {
        m_coords[0] = x;
        m_coords[1] = y;
        m_coords[2] = z;
    }
    Coordinate3D(const Coordinate3D& source)
    {
        m_coords[0] = source[0];
        m_coords[1] = source[1];
        m_coords[2] = source[2];
    }
    template <class U> Coordinate3D(const Coordinate3D<U>& source)
    {
        m_coords[0] = (T)source[0];
        m_coords[1] = (T)source[1];
        m_coords[2] = (T)source[2];
    }
    virtual ~Coordinate3D() {}

    inline T& operator[](const int index)
    {
        return m_coords[index%3];
    }
    inline const T& operator[](const int index) const
    {
        return m_coords[index%3];
    }
    inline Coordinate3D<T> &operator+=(const Coordinate3D<T> &right);
    inline Coordinate3D<T> &operator-=(const Coordinate3D<T> &right);
    inline Coordinate3D<T> &operator=(const Coordinate3D<T> &right);
    inline T norm()
    {
        return std::sqrt(m_coords[0]*m_coords[0]+m_coords[1]*m_coords[1]+m_coords[2]*m_coords[2]);
    }
protected:
private:
    T m_coords[3];
};

template <class T> inline Coordinate3D<T>& Coordinate3D<T>::operator+=(const Coordinate3D<T> &right)
{
    m_coords[0] += right[0];
    m_coords[1] += right[1];
    m_coords[2] += right[2];
    return *this;
}

template <class T> inline Coordinate3D<T>& Coordinate3D<T>::operator-=(const Coordinate3D<T> &right)
{
    m_coords[0] -= right[0];
    m_coords[1] -= right[1];
    m_coords[2] -= right[2];
    return *this;
}

template <class T> inline Coordinate3D<T> &Coordinate3D<T>::operator=(const Coordinate3D<T> &right)
{
    m_coords[0] = right[0];
    m_coords[1] = right[1];
    m_coords[2] = right[2];
    return *this;
}

template <class T> inline Coordinate3D<T> operator+(const Coordinate3D<T>& left, const Coordinate3D<T>& right)
{
    Coordinate3D<T> result = left;
    result += right;
    return result;
}

template <class T> inline Coordinate3D<T> operator-(const Coordinate3D<T>& vectorLeft, const Coordinate3D<T>& vectorRight)
{
    Coordinate3D<T> result = vectorLeft;
    result -= vectorRight;
    return result;
}

template <class T> inline Coordinate3D<T> CreateCoordinate3DFromPolar(T r, double theta, double phi)
{
    T x = r*gsl_sf_sin(theta)*gsl_sf_cos(phi);
    T y = r*gsl_sf_sin(theta)*gsl_sf_sin(phi);
    T z = r*gsl_sf_cos(theta);
    return Coordinate3D<T>(x, y, z);
}

template <class T> Coordinate3D<T> CrossProduct(const Coordinate3D<T> &left, const Coordinate3D<T> &right)
{
    T x = left[1]*right[2] - left[2]*right[1];
    T y = left[2]*right[0] - left[0]*right[2];
    T z = left[0]*right[1] - left[1]*right[0];
    return Coordinate3D<T>(x, y, z);
}

template <class T> T operator*(const Coordinate3D<T> &left, const Coordinate3D<T> &right)
{
    T x = left[0]*right[0];
    T y = left[1]*right[1];
    T z = left[2]*right[2];
    return x+y+z;
}

template <class T> Coordinate3D<T> operator*(const Coordinate3D<T> &left, const T &factor)
{
    T x = left[0]*factor;
    T y = left[1]*factor;
    T z = left[2]*factor;
    return Coordinate3D<T>(x, y, z);
}

template <class T> Coordinate3D<T> operator*(const T &factor, const Coordinate3D<T> &right)
{
    return right*factor;
}

template <class T> T GetDistanceBetweenPoints(const Coordinate3D<T> &left, const Coordinate3D<T> &right)
{
    Coordinate3D<T> connectingVector = left - right;
    return connectingVector.norm();
}

#endif /* COORDINATE3D_H_ */
