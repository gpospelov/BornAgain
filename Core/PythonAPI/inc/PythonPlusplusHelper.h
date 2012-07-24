#ifndef PYTHONPLUSPLUSHELPER_H
#define PYTHONPLUSPLUSHELPER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   PythonPlusplusHelper.h
//! @brief  Contains additional helper classes for Py++ code generator
//! @author Scientific Computing Group at FRM II
//! @date   02.06.2012

#include "Types.h"

// there is some weared behavior of pyplusplus
// without this definition it gets screwed up as soon as it sees in the code vector<kvector> like in LatticeBasis.h
namespace pyplusplus {
    namespace aliases {
        typedef KVector<double > kvector_t;
        typedef Geometry::Point3D<double > point3d_t;
        typedef Geometry::BasicVector3D<double > basicvector3d_t;
        typedef Geometry::Vector3D<double > vector3d_t;
    }
}

// class to help pyplusplus to expose kvector_t in python during automatic code generation
class PythonPlusplusHelper
{
public:
    size_t pyplusplus_boost_kvector() { return sizeof(kvector_t); }
//    size_t pyplusplus_boost_point3d() { return sizeof(Geometry::Point3D<double >); }
//    size_t pyplusplus_boost_basic3d() { return sizeof(Geometry::BasicVector3D<double >); }
//    size_t pyplusplus_boost_vector3d() { return sizeof(Geometry::Vector3D<double >); }
    size_t pyplusplus_boost_point3d() { return sizeof(point3d_t); }
    size_t pyplusplus_boost_basic3d() { return sizeof(basicvector3d_t); }
    size_t pyplusplus_boost_vector3d() { return sizeof(vector3d_t); }
};





#endif // PYTHONPLUSPLUSHELPER_H
