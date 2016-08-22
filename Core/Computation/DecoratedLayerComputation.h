// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DecoratedLayerComputation.h
//! @brief     Defines class DecoratedLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECORATEDLAYERCOMPUTATION_H
#define DECORATEDLAYERCOMPUTATION_H

#include "LayerComputation.h"

class IInterferenceFunctionStrategy;

//! Computes the scattering contribution from one layer with particles in/on it.
//! Controlled by MultiLayerComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ DecoratedLayerComputation : public LayerComputation
{
public:
    DecoratedLayerComputation(const Layer* p_layer, size_t layout_index=0);
    ~DecoratedLayerComputation() final;

    void run() final;

private:
    void runProtected() final;
    IInterferenceFunctionStrategy* createAndInitStrategy() const;
    void calculateCoherentIntensity(const IInterferenceFunctionStrategy* p_strategy);
    size_t m_layout_index;
};

#endif // DECORATEDLAYERCOMPUTATION_H
