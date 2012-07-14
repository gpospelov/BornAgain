#include "Types.h"



template<typename T>
KVector<T> &KVector<T>::operator=(const KVector<T> &other)
{
    m_x=other.m_x; m_y = other.m_y; m_z = other.m_z; //m_mag2 = other.m_mag2;
    return *this;
}

template<typename T> KVector<T> &KVector<T>::operator+=(const KVector<T> &b)
{
    m_x += b.m_x; m_y += b.m_y; m_z += b.m_z;
    //m_mag2 = m_x*m_x + m_y*m_y + m_z*m_z;
    return *this;
}

template<typename T> KVector<T> &KVector<T>::operator-=(const KVector<T> &b)
{
    m_x -= b.m_x; m_y -= b.m_y; m_z -= b.m_z;
    //m_mag2 = m_x*m_x + m_y*m_y + m_z*m_z;
    return *this;
}

template<typename T> KVector<T> operator+(const KVector<T> &a, const KVector<T> &b)
{
    KVector<T> target = a;
    target += b;
    return target;
}

template<typename T> KVector<T> operator-(const KVector<T> &a, const KVector<T> &b)
{
    KVector<T> target = a;
    target -= b;
    return target;
}

template<typename T>
std::ostream &operator<<(std::ostream &o, const KVector<T>  &a)
{
    o << a.m_x << " " << a.m_y << " " << a.m_z;
    return o;
}



// to force compiler to generate necessary code in shared library
template class KVector<double>;
//template KVector<double> operator=    <double> (const KVector<double> &a);
//template KVector<double> operator+=    <double> (const KVector<double> &a);
//template KVector<double> operator-=    <double> (const KVector<double> &a);
template KVector<double> operator+    <double> (const KVector<double> &a, const KVector<double> &b);
template KVector<double> operator-    <double> (const KVector<double> &a, const KVector<double> &b);
template std::ostream &operator<<    <double> (std::ostream &o, const KVector<double> &b);


