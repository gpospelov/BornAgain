// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarMLFresnelMap.h
//! @brief     Defines class ScalarMLFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SCALARMLFRESNELMAP_H
#define SCALARMLFRESNELMAP_H

#include "Hash2Doubles.h"
#include "IMultiLayerFresnelMap.h"
#include <unordered_map>
#include <utility>
#include <vector>

class ILayerRTCoefficients;
class MultiLayer;
class ScalarRTCoefficients;
class SimulationElement;

//! Implementation of IFresnelMap for scalar valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ ScalarMLFresnelMap : public IMultiLayerFresnelMap
{
public:
    ScalarMLFresnelMap();
    ~ScalarMLFresnelMap() final;

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element,
                       size_t layer_index) const override;

private:
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    const std::vector<ScalarRTCoefficients>& getCoefficientsFromCache(kvector_t kvec) const;

    mutable std::unordered_map<std::pair<double, double>, std::vector<ScalarRTCoefficients>,
                               Hash2Doubles> m_hash_table;
};

#endif // SCALARMLFRESNELMAP_H
