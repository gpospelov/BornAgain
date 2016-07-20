// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/DecoratedLayerDWBASimulation.h
//! @brief     Declares class DecoratedLayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECORATEDLAYERDWBASIMULATION_H
#define DECORATEDLAYERDWBASIMULATION_H

#include "LayerDWBASimulation.h" // inheriting from

class IInterferenceFunctionStrategy;

//! @class DecoratedLayerDWBASimulation
//! @ingroup algorithms_internal
//! @brief Calculates scattering cross sections in DWBA for a layer with particles in/on it

class BA_CORE_API_ DecoratedLayerDWBASimulation : public LayerDWBASimulation
{
public:
    DecoratedLayerDWBASimulation(const Layer* p_layer, size_t layout_index=0);
    virtual ~DecoratedLayerDWBASimulation();

    DecoratedLayerDWBASimulation* clone() const
    {
        throw Exceptions::NotImplementedException(
            "DecoratedLayerDWBASimulation::clone() -> Error: not implemented.");
    }

    virtual void run();
protected:
    virtual void runProtected();

private:
    IInterferenceFunctionStrategy* createAndInitStrategy() const;
    void calculateCoherentIntensity(const IInterferenceFunctionStrategy* p_strategy);
    size_t m_layout_index;
};

#endif // DECORATEDLAYERDWBASIMULATION_H
