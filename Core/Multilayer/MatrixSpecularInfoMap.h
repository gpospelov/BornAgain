// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixSpecularInfoMap.h
//! @brief     Defines class MatrixSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATRIXSPECULARINFOMAP_H
#define MATRIXSPECULARINFOMAP_H

#include "ILayerSpecularInfo.h"
#include <cstddef>

class ILayerRTCoefficients;
class MultiLayer;
class SimulationElement;

//! Implementation of ISpecularInfoMap for matrix valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixSpecularInfoMap : public ILayerSpecularInfo
{
public:
    MatrixSpecularInfoMap(const MultiLayer* p_multilayer, const MultiLayer* p_inverted_multilayer);
    ~MatrixSpecularInfoMap() final {}

    MatrixSpecularInfoMap* clone() const final override;

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients* getOutCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const final override;

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients* getInCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const final override;

private:
    const MultiLayer* mp_multilayer;
    const MultiLayer* mp_inverted_multilayer;
};

#endif // MATRIXSPECULARINFOMAP_H
