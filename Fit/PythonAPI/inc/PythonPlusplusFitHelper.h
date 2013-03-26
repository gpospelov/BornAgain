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

// there is some weared behavior of pyplusplus
// without this definition it gets screwed up as soon as it sees in the code vector<kvector> like in LatticeBasis.h
namespace pyplusplus {
    namespace aliases {
    typedef OutputData<double > ndimdata_t;
//    typedef OutputDataIterator<double, outputdata_t > outputdataiterator_t;
    typedef std::vector<double > vdouble1d_t;
//    typedef std::vector<vdouble1d_t > vdouble2d_t;
//    typedef std::vector<int > vint1d_t;
//    typedef std::vector<size_t > vsizet_t;
    }
}



// class to help pyplusplus to expose kvector_t in python during automatic code generation
class PythonPlusplusFitHelper
{
 public:
    size_t pyplusplus_boost_outputdata() { return sizeof(pyplusplus::aliases::ndimdata_t); }
//    size_t pyplusplus_boost_outputdata_iterator() { return sizeof(pyplusplus::aliases::outputdataiterator_t); }
    size_t pyplusplus_boost_vdouble1d() { return sizeof(pyplusplus::aliases::vdouble1d_t); }
};

#endif // PYTHONFITPLUSPLUSHELPER_H
