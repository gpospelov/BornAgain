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

#include <cstddef>
#include <vector>
#include "BasicVector3D.h"
using std::size_t;

typedef std::complex<double > complex_t;
typedef Geometry::BasicVector3D<double> kvector_t;
typedef Geometry::BasicVector3D<complex_t> cvector_t;
typedef std::vector<double > vdouble1d_t;
typedef std::vector<vdouble1d_t > vdouble2d_t;
typedef std::pair<complex_t, complex_t > complexpair_t;


#endif // TYPES_H
