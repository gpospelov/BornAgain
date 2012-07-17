#ifndef BASICVECTOR3D_H
#define BASICVECTOR3D_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   BasicVector3D.h
//! @brief  Basic properties and operation on 3-vectors
//! @author Scientific Computing Group at FRM II
//! @date   16.07.2012

#include <cmath>
#include <iostream>


//- -------------------------------------------------------------------
//! @class BasicVector3D
//! Basic properties and operation on 3-vectors
//- -------------------------------------------------------------------
class BasicVector3D
{
public:
    // ----------
    // constructors
    // ----------

    //! the constructor
    BasicVector3D(double x, double y, double z);
    //! the copy constructor.
    inline BasicVector3D(const BasicVector3D &v);
    //! assignment operator
    inline BasicVector3D & operator = (const BasicVector3D &v);
    ~BasicVector3D(){}

    // ----------
    // access
    // ----------

    //! return components in cartesian coordinate system.
    inline double x() const;
    inline double y() const;
    inline double z() const;
    //! The magnitude squared (r^2 in spherical coordinate system).
    inline double mag2() const;
    //! The magnitude (r in spherical coordinate system).
    inline double mag() const;
    //! The transverse component squared (rho^2 in cylindrical coordinate system).
    inline double perp2() const;
    //! The transverse component (rho in cylindrical coordinate system).
    inline double perp() const;

    // ----------
    // setters
    // ----------

    //! set the component in cartesian coordinate system.
    inline void setX(double);
    inline void setY(double);
    inline void setZ(double);
    //! set all three components in cartesian coordinate system.
    inline void set( double x, double y, double z);
    //! set in spherical coordinates
    inline void setRThetaPhi(double r, double theta, double phi);
    //! Set in cylindrical coordinates
    inline void setRhoPhiZ(double rho, double phi, double z);

    // ----------
    // comparison
    // ----------

    //! comparison operators
    inline bool operator == (const BasicVector3D &v) const;
    inline bool operator != (const BasicVector3D &v) const;
    //! ordering according to x,y,z components
    int compare (const BasicVector3D &v) const;
    bool operator > (const BasicVector3D &v) const;
    bool operator < (const BasicVector3D &v) const;
    bool operator>= (const BasicVector3D &v) const;
    bool operator<= (const BasicVector3D &v) const;

    // ----------
    // arithmetic
    // ----------

    //! addition
    inline BasicVector3D & operator += (const BasicVector3D &v);
    //! substraction
    inline BasicVector3D & operator -= (const BasicVector3D &v);
    //! unary minus.
    inline BasicVector3D operator - () const;
    //! scaling with real number
    inline BasicVector3D & operator *= (double);
    //! Division by real number
    inline BasicVector3D & operator /= (double);
    //! double product
    inline double dot(const BasicVector3D &v) const;
    //! cross product
    inline BasicVector3D cross(const BasicVector3D &v) const;

    // ----------
    // streams
    // ----------

    // output to a stream.
    friend std::ostream & operator << (std::ostream &, const BasicVector3D &v);

private:
    double m_x;
    double m_y;
    double m_z;
};

// -----------
// global arithmetics
// -----------

//! addition of 3-vectors.
inline BasicVector3D operator + (const BasicVector3D &v, const BasicVector3D &v);

//! Subtraction of 3-vectors.
inline BasicVector3D operator - (const BasicVector3D &v, const BasicVector3D &v);

//! Scaling of 3-vectors with a real number
inline BasicVector3D operator * (const BasicVector3D &v, double a);
inline BasicVector3D operator * (double a, const BasicVector3D &v);



/* ************************************************************************* */
// All inline definitions
/* ************************************************************************* */

// ------------
// constructors
// ------------

inline BasicVector3D::BasicVector3D(const BasicVector3D &v) : m_x(v.m_x), m_y(v.m_y), m_z(v.m_z) {}
inline BasicVector3D & BasicVector3D::operator = (const BasicVector3D &v) {
  m_x = v.m_x; m_y = v.m_y; m_x = v.m_z;
  return *this;
}

// ------------
// access
// ------------

// return components in cartesian coordinate system.
inline double BasicVector3D::x() const { return m_x; }
inline double BasicVector3D::y() const { return m_y; }
inline double BasicVector3D::z() const { return m_z; }
// the magnitude
inline double BasicVector3D::mag2() const { return m_x*m_x + m_y*m_y + m_z*m_z; }
inline double BasicVector3D::mag() const { return std::sqrt(mag2()); }
// the transverse component
inline double BasicVector3D::perp2() const { return m_x*m_x + m_y*m_y; }
inline double BasicVector3D::perp() const { return std::sqrt(perp2()); }

// ------------
// setters
// ------------

// set the component in cartesian coordinate system.
inline void BasicVector3D::setX(double x) { m_x = x; }
inline void BasicVector3D::setY(double y) { m_y = y; }
inline void BasicVector3D::setZ(double z) { m_z = z; }
inline void BasicVector3D::set(double x, double y, double z) { m_x = x; m_y = y; m_z = z; }
// set in spherical coordinates
inline void BasicVector3D::setRThetaPhi ( double r, double theta, double phi ) {
    m_z = r * std::cos(theta);
    double rho( r*std::sin(theta) );
    m_y = rho*std::sin(phi);
    m_x = rho*std::cos(phi);
}
// set in cyindrical coordinates
inline void BasicVector3D::setRhoPhiZ( double rho, double phi, double z)
{
    m_z = z;
    m_y = rho*std::sin (phi);
    m_x = rho*std::cos (phi);
}


// ----------
// comparison
// ----------

inline bool BasicVector3D::operator == (const BasicVector3D& v) const { return (v.x()==x() && v.y()==y() && v.z()==z()) ? true : false; }
inline bool BasicVector3D::operator != (const BasicVector3D& v) const { return (v.x()!=x() || v.y()!=y() || v.z()!=z()) ? true : false; }

// ----------
// arithmetic
// ----------
inline BasicVector3D& BasicVector3D::operator += (const BasicVector3D &v) {
  m_x += v.x(); m_y += v.y(); m_z += v.z();
  return *this;
}

inline BasicVector3D& BasicVector3D::operator -= (const BasicVector3D &v) {
  m_x -= v.x(); m_y -= v.y(); m_z -= v.z();
  return *this;
}

inline BasicVector3D BasicVector3D::operator - () const { return BasicVector3D(-m_x, -m_y, -m_z); }

inline BasicVector3D& BasicVector3D::operator *= (double a) {
  m_x *= a; m_y *= a; m_z *= a;
  return *this;
}

inline BasicVector3D& BasicVector3D::operator /= (double a) {
  m_x /= a; m_y /= a; m_z /= a;
  return *this;
}

inline double BasicVector3D::dot(const BasicVector3D &v) const {
  return m_x*v.x() + m_y*v.y() + m_z*v.z();
}

inline BasicVector3D BasicVector3D::cross(const BasicVector3D &v) const {
  return BasicVector3D(m_y*v.z()-v.y()*m_z, m_z*v.x()-v.z()*m_x, m_x*v.y()-v.x()*m_y);
}

// -----------------
// global arithmetic
// -----------------

inline BasicVector3D operator + (const BasicVector3D & a, const BasicVector3D & b) {
  return BasicVector3D(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}

inline BasicVector3D operator - (const BasicVector3D & a, const BasicVector3D & b) {
  return BasicVector3D(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

inline BasicVector3D operator * (const BasicVector3D &v, double a) {
  return BasicVector3D(a*v.x(), a*v.y(), a*v.z());
}

inline BasicVector3D operator * (double a, const BasicVector3D &v) {
  return BasicVector3D(a*v.x(), a*v.y(), a*v.z());
}



#endif // BASICVECTOR3D_H
