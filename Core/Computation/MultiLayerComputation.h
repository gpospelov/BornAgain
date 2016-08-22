// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MultiLayerComputation.h
//! @brief     Defines class MultiLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERCOMPUTATION_H
#define MULTILAYERCOMPUTATION_H

#include "Computation.h"
#include "Complex.h"
#include <map>

class LayerComputation;
class MultiLayer;
class MultiLayerRoughnessComputation;

//! Performs a DWBA calculation with given sample and simulation parameters
//! @ingroup algorithms_internal

class BA_CORE_API_ MultiLayerComputation : public Computation
{
public:
    MultiLayerComputation(const MultiLayer* p_multi_layer);
    ~MultiLayerComputation() final;
    MultiLayerComputation* clone() const final;

    void init(
        const SimulationOptions& options,
        const Simulation& simulation,
        std::vector<SimulationElement>::iterator begin_it,
        std::vector<SimulationElement>::iterator end_it) final;

    void run() final;

protected:
    void runProtected() final;

    //! calculates intensity map for samples with magnetization
    void collectRTCoefficientsScalar();
    void collectRTCoefficientsMatrix();

    std::map<size_t, SafePointerVector<LayerComputation>> m_layer_dwba_simulations_map;
    MultiLayer* mp_multi_layer;
    MultiLayerRoughnessComputation* mp_roughness_dwba_simulation;
};

#endif // MULTILAYERCOMPUTATION_H
