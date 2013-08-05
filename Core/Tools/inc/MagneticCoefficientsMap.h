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
    typedef Utils::UnorderedMap<double, SpecularMagnetic::LayerMatrixCoeff>
        container_t;

    MagneticCoefficientsMap(){}
    MagneticCoefficientsMap(const container_t& value_map) : m_value_map(value_map) {}

    SpecularMagnetic::LayerMatrixCoeff&  operator[] (double key) {
        return m_value_map[key];
    }
    MagneticCoefficientsMap *clone() const {
        return new MagneticCoefficientsMap(m_value_map);
    }
    const SpecularMagnetic::LayerMatrixCoeff& evaluate(double value) const {
        return m_value_map.find(value);
    }
 private:
    container_t m_value_map;
};

//! Double to pair of complex unordered map.




#endif /* MAGNETICCOEFFICIENTSMAP_H_ */
