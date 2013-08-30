// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/MagneticCoefficientsMap.h
//! @brief     Defines class MagneticCoefficientsMap.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MAGNETICCOEFFICIENTSMAP_H_
#define MAGNETICCOEFFICIENTSMAP_H_

#include "Utils.h"
#include "SpecularMagnetic.h"

//! Map from angles (double) to matrix coefficients for magnetic
//! DWBA calculation.

class MagneticCoefficientsMap
{
public:
    typedef Utils::UnorderedMap<double, MatrixRTCoefficients>
        container_phi_t;
    typedef Utils::UnorderedMap<double, container_phi_t> container_t;

    MagneticCoefficientsMap(){}
    MagneticCoefficientsMap(const container_t& value_map,
            MatrixRTCoefficients incoming_coeff)
            : m_value_map(value_map)
            , m_incoming_coeff(incoming_coeff) {}

    MagneticCoefficientsMap *clone() const;

    container_phi_t&  operator[] (double key) {
        return m_value_map[key];
    }

    const container_phi_t& evaluate(double value) const {
        return m_value_map.find(value);
    }

    MatrixRTCoefficients& incomingCoeff() {
        return m_incoming_coeff;
    }
private:
    container_t m_value_map;
    MatrixRTCoefficients m_incoming_coeff;
};

inline MagneticCoefficientsMap* MagneticCoefficientsMap::clone() const
{
    return new MagneticCoefficientsMap(m_value_map, m_incoming_coeff);
}

#endif /* MAGNETICCOEFFICIENTSMAP_H_ */
