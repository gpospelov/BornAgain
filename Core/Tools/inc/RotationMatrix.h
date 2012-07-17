#ifndef ROTATION_H
#define ROTATION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   RotationMatrix.h
//! @brief  Definition of RotationMatrix class to perform rotation of BasicVector3D objects
//! @author Scientific Computing Group at FRM II
//! @date   16.07.2012

#include <cmath>
#include <iostream>


//- -------------------------------------------------------------------
//! @class RotationMatrix
//! Definition of RotationMatrix class to perform rotation of BasicVector3D objects
//- -------------------------------------------------------------------
class RotationMatrix
{
public:
    // ----------
    // aconstructors
    // ----------
    //! default constructor, gives a unit matrix
    RotationMatrix();
    //! copy constructor
    RotationMatrix(const RotationMatrix &m);
    //! construct from three Euler angles (in radians)
    RotationMatrix( double phi, double theta, double psi );

    // ----------
    // getters
    // ----------
    //! access to euler angles
    double getPhi() const;
    double getTheta() const;
    double getPsi() const;

    // ----------
    // setters
    // ----------
    //! change Euler angle phi
    void setPhi (double phi);
    //! change Euler angle theta
    void setTheta (double theta);
    //! change Euler angle psi
    void setPsi (double psi);
    //! set three Euler angles (in radians)
    RotationMatrix & set( double phi, double theta, double psi );

protected:
    //! construct from 9 matrix elements
    RotationMatrix(double mxx, double mxy, double mxz,
                   double myx, double myy, double myz,
                   double mzx, double mzy, double mzz);

    double rxx, rxy, rxz,
           ryx, ryy, ryz,
           rzx, rzy, rzz; //!< matrix elements
};


/* ************************************************************************* */
// All inline definitions
/* ************************************************************************* */

//inline double  RotationMatrix::getPhi() const { return phi();   }
//inline double  RotationMatrix::getTheta() const { return theta(); }
//inline double  RotationMatrix::getPsi() const { return psi();   }


#endif // ROTATION_H
