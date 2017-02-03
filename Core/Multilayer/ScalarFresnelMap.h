// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarFresnelMap.h
//! @brief     Defines class ScalarFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SCALARFRESNELMAP_H
#define SCALARFRESNELMAP_H

#include "HashKVector.h"
#include "IFresnelMap.h"
#include <unordered_map>
#include <vector>

class MultiLayer;
class ILayerRTCoefficients;
class ScalarRTCoefficients;
class SimulationElement;

//! Implementation of IFresnelMap for scalar valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ ScalarFresnelMap : public IFresnelMap
{
public:
    ScalarFresnelMap(const MultiLayer* multilayer);
    ~ScalarFresnelMap() final;

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients* getOutCoefficients (
        const SimulationElement& sim_element, size_t layer_index) const final override;

    //! Retrieves the amplitude coefficients for the given angles
    const ILayerRTCoefficients* getInCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const final override;

private:
    const MultiLayer* mp_multilayer;
    const ScalarRTCoefficients* getCoefficients(kvector_t kvec, size_t layer_index) const;
    mutable std::unordered_map<kvector_t, std::vector<ScalarRTCoefficients>,
                               HashKVector> m_hash_table;
};

#endif // SCALARFRESNELMAP_H
