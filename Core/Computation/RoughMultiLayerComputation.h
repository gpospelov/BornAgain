// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/RoughMultiLayerComputation.h
//! @brief     Defines class RoughMultiLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERROUGHNESSCOMPUTATION_H
#define MULTILAYERROUGHNESSCOMPUTATION_H

#include "Computation.h"
#include "Complex.h"

class LayerSpecularInfo;
class MultiLayer;

//! Computes the diffuse reflection from the rough interfaces of a multilayer.
//! Controlled by MainComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ RoughMultiLayerComputation : public Computation
{
public:
    RoughMultiLayerComputation(const MultiLayer* p_multi_layer);
    ~RoughMultiLayerComputation() final;

    void run() final;

    //! Sets magnetic reflection/transmission info for specific layer
    void setSpecularInfo(size_t i_layer, const LayerSpecularInfo& specular_info);

    // evaluate
    double evaluate(const SimulationElement& sim_element);

protected:
    void runProtected() final;

    complex_t get_refractive_term(size_t ilayer) const;
    complex_t get_sum8terms(size_t ilayer, const SimulationElement& sim_element);

    MultiLayer* mp_multi_layer;
    std::vector<LayerSpecularInfo*> mp_specular_info_vector;
};

#endif // MULTILAYERROUGHNESSCOMPUTATION_H
