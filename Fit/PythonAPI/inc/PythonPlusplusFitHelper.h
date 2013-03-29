#ifndef PYTHONFITPLUSPLUSHELPER_H
#define PYTHONFITPLUSPLUSHELPER_H
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
//! @date   19.03.2013


#include "OutputData.h"
#include "Types.h"



// this is special namespace to help Py++ generate correct names
namespace pyplusplus {
    namespace aliases {
//    typedef OutputData<double > ndimdata_t;
//    typedef OutputDataIterator<double, ndimdata_t > ndimiterator_t;
    typedef std::vector<double > vdouble1d_t;
    typedef std::vector<vdouble1d_t > vdouble2d_t;
//    typedef std::vector<int > vint1d_t;
//    typedef std::vector<size_t > vsizet_t;
    typedef std::vector<complex_t > vcomplex1d_t;
    }
}


// helper class to provide Py++ with explicit template instantiations
class PythonPlusplusFitHelper
{
 public:
//    size_t pyplusplus_boost_outputdata() { return sizeof(pyplusplus::aliases::ndimdata_t); }
//    size_t pyplusplus_boost_outputdata_iterator() { return sizeof(pyplusplus::aliases::ndimiterator_t); }
    size_t pyplusplus_boost_vdouble1d() { return sizeof(pyplusplus::aliases::vdouble1d_t); }
    size_t pyplusplus_boost_vcomplex1d() { return sizeof(pyplusplus::aliases::vcomplex1d_t); }
};

#endif // PYTHONFITPLUSPLUSHELPER_H
