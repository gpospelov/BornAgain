// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/MatrixSpecularInfoMap.h
//! @brief     Defines class MatrixSpecularInfoMap.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATRIXSPECULARINFOMAP_H_
#define MATRIXSPECULARINFOMAP_H_

#include "ISpecularInfoMap.h"
#include "Utils.h"


//! @class MatrixSpecularInfoMap
//! @ingroup algorithms_internal
//! @brief Implementation of ISpecularInfoMap for matrix valued reflection/
//! transmission coefficients (the map contains values for both alpha_f and
//! phi_f, because of broken rotation symmetry in the xy-plane

class BA_CORE_API_ MatrixSpecularInfoMap : public ISpecularInfoMap
{
public:
    MatrixSpecularInfoMap() {}
    virtual ~MatrixSpecularInfoMap() {}

    //! Adds amplitude coefficients for the given angles
    void addCoefficients(const MatrixRTCoefficients &rt_coefficients,
            double alpha_f, double phi_f);

    //! Retrieves the amplitude coefficients for the given angles
    virtual const MatrixRTCoefficients *getCoefficients(
            double alpha_f, double phi_f) const;
private:
    typedef Utils::UnorderedMap<double, MatrixRTCoefficients>
        container_phi_t;
    Utils::UnorderedMap<double, container_phi_t> m_value_map;
};

inline void MatrixSpecularInfoMap::addCoefficients(
        const MatrixRTCoefficients& rt_coefficients, double alpha_f,
        double phi_f)
{
    container_phi_t &phi_map = m_value_map[alpha_f];
    phi_map[phi_f] = rt_coefficients;
}

inline const MatrixRTCoefficients* MatrixSpecularInfoMap::getCoefficients(
        double alpha_f, double phi_f) const
{
    const container_phi_t &phi_map = m_value_map.find(alpha_f);
    return &phi_map.find(phi_f);
}


#endif /* MATRIXSPECULARINFOMAP_H_ */
