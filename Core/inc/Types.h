#ifndef TYPES_H
#define TYPES_H


#include <complex>
#include <vector>


typedef std::complex<double > complex_t;


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
private:
    T m_x;
    T m_y;
    T m_z;
    T m_mag2;
};
typedef KVector<double >  kvector_t;


#endif // TYPES_H
