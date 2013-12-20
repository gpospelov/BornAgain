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
#include "DiffuseParticleInfo.h"
#include "IFormFactor.h"
#include "MaterialManager.h"
#include "IStochasticParameter.h"
#include "OutputData.h"
#include "ISampleBuilder.h"

//! this is special namespace to help Py++ generate correct names
namespace pyplusplus {
    namespace aliases {
        using namespace Geometry;
        //typedef Geometry::BasicVector3D<double > kvector_t;
        typedef BasicVector3D<double > kvector_t;
        typedef std::vector<kvector_t > vector_kvector_t;
        typedef BasicVector3D<std::complex<double> > cvector_t;
        typedef std::vector<cvector_t > vector_cvector_t;
        typedef std::vector<DiffuseParticleInfo *> vector_DiffuseParticleInfoPtr_t;
        typedef std::vector<IFormFactor *> vector_IFormFactorPtr_t;
        typedef ISingleton<MaterialManager> MaterialManagerSingleton_t;
        typedef StochasticParameter<double> StochasticParameter_t;
        typedef OutputData<double > IntensityData;
        typedef std::vector<int > vector_integer_t;
        typedef std::vector<unsigned long int > vector_longinteger_t;
        //typedef boost::shared_ptr<class ISampleBuilder > SampleBuilder_t;
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
    inline size_t pyplusplus_boost_vectorof_DiffuseParticleInfoPtr() { return sizeof(pyplusplus::aliases::vector_DiffuseParticleInfoPtr_t); }
    inline size_t pyplusplus_boost_stochastic_parameter() { return sizeof(pyplusplus::aliases::StochasticParameter_t); }
    inline size_t pyplusplus_boost_vector_integer() { return sizeof(pyplusplus::aliases::vector_integer_t); }
    inline size_t pyplusplus_boost_vector_longinteger() { return sizeof(pyplusplus::aliases::vector_longinteger_t); }
    inline size_t pyplusplus_boost_intensity_data() { return sizeof(pyplusplus::aliases::IntensityData); }
    //inline size_t pyplusplus_boost_sample_builder() { return sizeof(pyplusplus::aliases::SampleBuilder_t); }
}

#endif // PYTHONCOREEXPOSER_H


