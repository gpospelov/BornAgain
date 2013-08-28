// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/OpticalFresnel.h
//! @brief     Defines class OpticalFresnel.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OPTICALFRESNEL_H
#define OPTICALFRESNEL_H

#include <vector>
#include "Types.h"
#include "ISimulation.h"
#include "MultiLayer.h"
#include "ScalarRTCoefficients.h"

//! Optical Fresnel coefficients.

class OpticalFresnel : public ISimulation
{
public:
    OpticalFresnel() : m_use_roughness(false) {}

    //! collection of reflection/transmission coefficients for multi layer
    class MultiLayerCoeff
    {
    public:
        inline ScalarRTCoefficients& operator[](size_t i) { return m_data[i]; }
        inline const ScalarRTCoefficients& operator[](size_t i) const {
            return m_data[i];
        }
        inline size_t size() const { return m_data.size(); }
        inline void clear() { m_data.clear(); }
        inline void resize(size_t size) { m_data.resize(size); }
    private:
        std::vector<ScalarRTCoefficients > m_data;
    };

    //! set of reflection/transmission coefficients for set of layers, [nlayer]
    typedef MultiLayerCoeff MultiLayerCoeff_t;
    //! Returns reflection/transmission coefficients for given multi layer
    //! and kvector
    void execute(const MultiLayer& sample, const kvector_t& k,
            MultiLayerCoeff_t& coeff);

private:
    bool m_use_roughness;

    void calculateKZ(const MultiLayer& sample, const kvector_t& k,
            MultiLayerCoeff_t& coeff) const;
    void calculateFresnelCoefficients(const MultiLayer& sample,
            MultiLayerCoeff_t& coeff) const;
    void calculateX(const MultiLayer& sample, MultiLayerCoeff_t& coeff) const;
    void calculateRT(const MultiLayer& sample, MultiLayerCoeff_t& coeff) const;
};

#endif // OPTICALFRESNEL_H


