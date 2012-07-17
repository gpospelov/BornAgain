#include "BasicVector3D.h"


BasicVector3D::BasicVector3D(double x, double y, double z) :
    m_x(x), m_y(y), m_z(z)
{

}


int BasicVector3D::compare (const BasicVector3D &v) const
{
  if       ( m_z > v.m_z ) {
    return 1;
  } else if ( m_z < v.m_z ) {
    return -1;
  } else if ( m_y > v.m_y ) {
    return 1;
  } else if ( m_y < v.m_y ) {
    return -1;
  } else if ( m_x > v.m_x ) {
    return 1;
  } else if ( m_x < v.m_x ) {
    return -1;
  } else {
    return 0;
  }
}

bool BasicVector3D::operator > (const BasicVector3D & v) const { return (compare(v)  > 0); }
bool BasicVector3D::operator < (const BasicVector3D & v) const { return (compare(v)  < 0); }
bool BasicVector3D::operator>= (const BasicVector3D & v) const { return (compare(v) >= 0); }
bool BasicVector3D::operator<= (const BasicVector3D & v) const { return (compare(v) <= 0); }

std::ostream & operator<< (std::ostream & os, const BasicVector3D & v) {
  return os << "(" << v.x() << "," << v.y() << "," << v.z() << ")";
}

