#ifndef TYPES_H
#define TYPES_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Types.h
//! @brief  Definition of Types
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include <complex>
#include <vector>


typedef std::complex<double > complex_t;

// we need forward declaration here to be able to redefine ostream as friend
template<typename T> class KVector;
template<typename T> std::ostream& operator<< (std::ostream& o, const KVector<T>& );


template<typename T>
class KVector {
public:
    KVector() : m_x(0), m_y(0), m_z(0), m_mag2(0) {}
    KVector(T x, T y, T z) : m_x(x), m_y(y), m_z(z), m_mag2(0) {}
    void setMagThetaPhi(T mag, T theta, T phi)
    {
        T amag = std::abs(mag);
        m_x = amag * std::sin(theta) * std::cos(phi);
        m_y = amag * std::sin(theta) * std::sin(phi);
        m_z = amag * std::cos(theta);
        m_mag2 = m_x*m_x + m_y*m_y + m_z*m_z;
    }
    void setLambdaAlphaPhi(T lambda, T alpha, T phi)
    {
        T k = 2.*M_PI/lambda;
        m_x = k*std::cos(alpha) * std::cos(phi);
        m_y = k*std::cos(alpha) * std::sin(phi);
        m_z = k*std::sin(alpha);
        m_mag2 = m_x*m_x + m_y*m_y + m_z*m_z;
    }
    inline T x() const { return m_x; }
    inline T y() const { return m_y; }
    inline T z() const { return m_z; }
    inline T mag() const { return std::sqrt(m_mag2); }
    inline T mag2() const { return m_mag2; }
    inline T magxy() const { return std::sqrt(m_x*m_x+m_y*m_y); }

    KVector<T> &operator=(const KVector<T> &other);
    KVector<T> &operator+=(const KVector<T> &other);
    KVector<T> &operator-=(const KVector<T> &other);
    friend std::ostream &operator<< <> (std::ostream &ostr, KVector<T> const &k);

    static KVector<T> LambdaAlphaPhi(T lambda, T alpha, T phi)
    {
            KVector<T> k; k.setLambdaAlphaPhi(lambda, alpha, phi);
            return k;
    }

private:
    T m_x;
    T m_y;
    T m_z;
    T m_mag2;
};

template<typename T> KVector<T> operator+(const KVector<T> &a, const KVector<T> &b);
template<typename T> KVector<T> operator-(const KVector<T> &a, const KVector<T> &b);

//template<typename T>
//inline KVector<T> LambdaAlphaPhi(T lambda, T alpha, T phi)
//{
//    KVector<T> k;
//    k.setLambdaAlphaPhi(lambda, alpha, phi);
//}


typedef KVector<double>  kvector_t;

//typedef KVector<complex_t> complex_vector_t;
//
//inline complex_vector_t getComplexVector(kvector_t real_vector)
//{
//	return complex_vector_t(complex_t(real_vector.x()),
//			complex_t(real_vector.y()), complex_t(real_vector.z()));
//}


#endif // TYPES_H
