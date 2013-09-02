// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ScalarSpecularInfoMap.h
//! @brief     Defines class ScalarSpecularInfoMap.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SCALARSPECULARINFOMAP_H_
#define SCALARSPECULARINFOMAP_H_

#include "ISpecularInfoMap.h"
#include "Utils.h"

#include <boost/shared_ptr.hpp>

class ScalarSpecularInfoMap : public ISpecularInfoMap
{
public:
    ScalarSpecularInfoMap() {}
    virtual ~ScalarSpecularInfoMap() {}

    //! Adds amplitude coefficients for the given angles
    virtual void addCoefficients(ILayerRTCoefficients *rt_coefficients,
            double alpha_f, double phi_f);

    //! Retrieves the amplitude coefficients for the given angles
    virtual const ScalarRTCoefficients *getCoefficients(
            double alpha_f, double phi_f) const;
private:
    Utils::UnorderedMap<double, ScalarRTCoefficients > m_value_map;
};

inline void ScalarSpecularInfoMap::addCoefficients(
        ILayerRTCoefficients* rt_coefficients, double alpha_f, double phi_f)
{
    m_value_map[alpha_f] = *rt_coefficients;
}

inline const ScalarRTCoefficients* ScalarSpecularInfoMap::getCoefficients(
        double alpha_f, double phi_f) const
{
    (void)phi_f;
    return &m_value_map[alpha_f];
}

#endif /* SCALARSPECULARINFOMAP_H_ */
