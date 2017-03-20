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

#include "Hash2Doubles.h"
#include "IFresnelMap.h"
#include "Vectors3D.h"
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

class ILayerRTCoefficients;
class MultiLayer;
class ScalarRTCoefficients;
class SimulationElement;

//! Implementation of IFresnelMap for scalar valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ ScalarFresnelMap : public IFresnelMap
{
public:
    ScalarFresnelMap(const MultiLayer& multilayer);
    ~ScalarFresnelMap() final;

    const ILayerRTCoefficients* getOutCoefficients (
        const SimulationElement& sim_element, size_t layer_index) const final override;

    const ILayerRTCoefficients* getInCoefficients(
        const SimulationElement& sim_element, size_t layer_index) const final override;

    void setMultilayer(const MultiLayer& multilayer) final override;

private:
    std::unique_ptr<MultiLayer> mP_multilayer;
    const ScalarRTCoefficients* getCoefficients(kvector_t kvec, size_t layer_index) const;
    mutable std::unordered_map<std::pair<double, double>, std::vector<ScalarRTCoefficients>,
                               Hash2Doubles> m_hash_table;
};

#endif // SCALARFRESNELMAP_H
