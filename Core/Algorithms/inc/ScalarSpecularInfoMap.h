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
#include "ScalarRTCoefficients.h"
#include "Utils.h"

//! Implementation of ISpecularInfoMap for scalar valued reflection/
//! transmission coefficients (the map contains values only for alpha_f,
//! because of rotation symmetry in the xy-plane

class ScalarSpecularInfoMap : public ISpecularInfoMap
{
public:
    ScalarSpecularInfoMap() {}
    virtual ~ScalarSpecularInfoMap() {}

    //! Adds amplitude coefficients for the given angles
    void addCoefficients(const ScalarRTCoefficients &rt_coefficients,
            double alpha_f, double phi_f);

    //! Retrieves the amplitude coefficients for the given angles
    virtual const ScalarRTCoefficients *getCoefficients(
            double alpha_f, double phi_f) const;
private:
    Utils::UnorderedMap<double, ScalarRTCoefficients > m_value_map;
};

inline void ScalarSpecularInfoMap::addCoefficients(
        const ScalarRTCoefficients& rt_coefficients, double alpha_f,
        double phi_f)
{
    (void)phi_f;
    m_value_map[alpha_f] = rt_coefficients;
}

inline const ScalarRTCoefficients* ScalarSpecularInfoMap::getCoefficients(
        double alpha_f, double phi_f) const
{
    (void)phi_f;
    return &m_value_map.find(alpha_f);
}

#endif /* SCALARSPECULARINFOMAP_H_ */
