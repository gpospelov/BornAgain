#include "RotationMatrix.h"


/* ************************************************************************* */
// All inline definitions
/* ************************************************************************* */
RotationMatrix::RotationMatrix() : rxx(1.0), rxy(0.0), rxz(0.0),
                                   ryx(0.0), ryy(1.0), ryz(0.0),
                                   rzx(0.0), rzy(0.0), rzz(1.0)
{
}


RotationMatrix::RotationMatrix ( const RotationMatrix & m ) :
    rxx(m.rxx), rxy(m.rxy), rxz(m.rxz),
    ryx(m.ryx), ryy(m.ryy), ryz(m.ryz),
    rzx(m.rzx), rzy(m.rzy), rzz(m.rzz)
{
}


// construct from 9 matrix elements
RotationMatrix::RotationMatrix(double mxx, double mxy, double mxz,
                               double myx, double myy, double myz,
                               double mzx, double mzy, double mzz) :
    rxx(mxx), rxy(mxy), rxz(mxz),
    ryx(myx), ryy(myy), ryz(myz),
    rzx(mzx), rzy(mzy), rzz(mzz)
{
}

// construct from 3 Euler angles
RotationMatrix::RotationMatrix( double phi, double theta, double psi )
{
    set(phi, theta, psi);
}

// set three Euler angles (in radians)
RotationMatrix & RotationMatrix::set(double phi, double theta, double psi)
{
    double sinPhi   = std::sin( phi   );
    double cosPhi   = std::cos( phi   );
    double sinTheta = std::sin( theta );
    double cosTheta = std::cos( theta );
    double sinPsi   = std::sin( psi   );
    double cosPsi   = std::cos( psi   );

    rxx =   cosPsi * cosPhi - cosTheta * sinPhi * sinPsi;
    rxy =   cosPsi * sinPhi + cosTheta * cosPhi * sinPsi;
    rxz =   sinPsi * sinTheta;

    ryx = - sinPsi * cosPhi - cosTheta * sinPhi * cosPsi;
    ryy = - sinPsi * sinPhi + cosTheta * cosPhi * cosPsi;
    ryz =   cosPsi * sinTheta;

    rzx =   sinTheta * sinPhi;
    rzy = - sinTheta * cosPhi;
    rzz =   cosTheta;

  return  *this;
}
