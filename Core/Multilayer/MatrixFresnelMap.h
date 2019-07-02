// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixFresnelMap.h
//! @brief     Defines class MatrixFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATRIXFRESNELMAP_H
#define MATRIXFRESNELMAP_H

#include "HashKVector.h"
#include "IFresnelMap.h"
#include "MatrixRTCoefficients.h"
#include <memory>
#include <unordered_map>
#include <vector>

class ILayerRTCoefficients;
class Slice;
class SimulationElement;

//! Implementation of IFresnelMap for matrix valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixFresnelMap : public IFresnelMap
{
public:
    MatrixFresnelMap();
    ~MatrixFresnelMap() override;

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element,
                       size_t layer_index) const final override;

    void setSlices(const std::vector<Slice>& slices) final override;

    typedef std::unordered_map<kvector_t, std::vector<MatrixRTCoefficients>, HashKVector>
        CoefficientHash;

private:
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index,
                                                                const std::vector<Slice>& slices,
                                                                CoefficientHash& hash_table) const;
    std::vector<Slice> m_inverted_slices;
    mutable CoefficientHash m_hash_table_out;
    mutable CoefficientHash m_hash_table_in;
};

#endif // MATRIXFRESNELMAP_H
