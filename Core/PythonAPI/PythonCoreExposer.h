// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/inc/PythonCoreExposer.h
//! @brief     Helpers for automatic PythonAPI generation
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYTHONCOREEXPOSER_H
#define PYTHONCOREEXPOSER_H

#include "Types.h"
#include "BasicVector3D.h"
#include "IFormFactor.h"
#include "OutputData.h"
#include "ISampleBuilder.h"
#include "FTDistributions.h"
#include "RealParameterWrapper.h"

//! this is special namespace to help Py++ generate correct names
namespace pyplusplus {
    namespace aliases {
        using namespace Geometry;
        typedef BasicVector3D<double > kvector_t;
        typedef std::vector<kvector_t > vector_kvector_t;
        typedef BasicVector3D<std::complex<double> > cvector_t;
        typedef std::vector<cvector_t > vector_cvector_t;
        typedef std::vector<IFormFactor *> vector_IFormFactorPtr_t;
        typedef OutputData<double > IntensityData;
        typedef std::vector<int > vector_integer_t;
        typedef std::vector<unsigned long int > vector_longinteger_t;
        typedef std::vector<complex_t> vector_complex_t;
        typedef std::vector<std::string> vector_string_t;
        typedef std::vector<RealParameterWrapper> vector_realparameter_t;
//        typedef std::vector<ParameterSample> vector_ParameterSample_t;
        typedef std::vector<double> vdouble1d_t;
        typedef std::vector<vdouble1d_t> vdouble2d_t;
    }
}

//! helper function to set value via subscript operator from python
template <class Self, class Key, class Value>
void pyplusplus_setitem(Self& self, Key const& key, Value const& value)
{
    self[key] = value;
}

//! functions to help Py++ with template instantiation
namespace pyplusplus {
    inline size_t pyplusplus_boost_kvector() { return sizeof(pyplusplus::aliases::kvector_t); }
    inline size_t pyplusplus_boost_vectorof_kvector() { return sizeof(pyplusplus::aliases::vector_kvector_t); }
    inline size_t pyplusplus_boost_cvector() { return sizeof(pyplusplus::aliases::cvector_t); }
    inline size_t pyplusplus_boost_vectorof_cvector() { return sizeof(pyplusplus::aliases::vector_cvector_t); }
    inline size_t pyplusplus_boost_vector_integer() { return sizeof(pyplusplus::aliases::vector_integer_t); }
    inline size_t pyplusplus_boost_vector_longinteger() { return sizeof(pyplusplus::aliases::vector_longinteger_t); }
    inline size_t pyplusplus_boost_intensity_data() { return sizeof(pyplusplus::aliases::IntensityData); }
    inline size_t pyplusplus_boost_vector_complex() { return sizeof(pyplusplus::aliases::vector_complex_t); }
    inline size_t pyplusplus_boost_vector_string() { return sizeof(pyplusplus::aliases::vector_string_t); }
    inline size_t pyplusplus_boost_vector_realparameter() { return sizeof(pyplusplus::aliases::vector_realparameter_t); }
//    inline size_t pyplusplus_boost_vector_ParameterSample() { return sizeof(pyplusplus::aliases::vector_ParameterSample_t); }
    inline size_t pyplusplus_boost_vector_vdouble2d_t() { return sizeof(pyplusplus::aliases::vdouble2d_t); }
}

#endif // PYTHONCOREEXPOSER_H


