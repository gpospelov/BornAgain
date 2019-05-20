// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixMLFresnelMap.h
//! @brief     Defines class MatrixMLFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATRIXMLFRESNELMAP_H
#define MATRIXMLFRESNELMAP_H

#include "HashKVector.h"
#include "IMultiLayerFresnelMap.h"
#include <memory>
#include <unordered_map>
#include <vector>

class ILayerRTCoefficients;
class MatrixRTCoefficients;
class MultiLayer;
class SimulationElement;

//! Implementation of IFresnelMap for matrix valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixMLFresnelMap : public IMultiLayerFresnelMap
{
public:
    MatrixMLFresnelMap();
    ~MatrixMLFresnelMap() override;

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element,
                       size_t layer_index) const final override;

    void setMultilayer(const MultiLayer& multilayer) final override;

    typedef std::unordered_map<kvector_t, std::vector<MatrixRTCoefficients>, HashKVector>
        CoefficientMap;

private:
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index,
                                                                const MultiLayer& multilayer,
                                                                CoefficientMap& hash_table) const;

    std::unique_ptr<MultiLayer> mP_inverted_multilayer;
    mutable CoefficientMap m_hash_table_out;
    mutable CoefficientMap m_hash_table_in;
};

#endif // MATRIXMLFRESNELMAP_H
