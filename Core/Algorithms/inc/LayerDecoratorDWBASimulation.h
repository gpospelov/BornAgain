// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/LayerDecoratorDWBASimulation.h
//! @brief     Defines class LayerDecoratorDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef LAYERDECORATORDWBASIMULATION_H_
#define LAYERDECORATORDWBASIMULATION_H_

#include "LayerDWBASimulation.h"
#include "DiffuseDWBASimulation.h"
#include "IInterferenceFunctionStrategy.h"

class LayerDecorator;

//! Calculates scattering cross sections in DWBA for a layer with particles in/on it

class LayerDecoratorDWBASimulation : public LayerDWBASimulation
{
public:
    LayerDecoratorDWBASimulation(const LayerDecorator *p_layer_decorator);
    virtual ~LayerDecoratorDWBASimulation();

    LayerDecoratorDWBASimulation *clone() const { throw NotImplementedException("LayerDecoratorDWBASimulation::clone() -> Error: not implemented."); }

    virtual void init(const Simulation &simulation);

    virtual void run();
protected:
    LayerDecorator *mp_layer_decorator;
    DiffuseDWBASimulation *mp_diffuseDWBA;

private:
    IInterferenceFunctionStrategy *createAndInitStrategy() const;
    std::vector<IFormFactor *> createDWBAFormFactors() const;
    void calculateCoherentIntensity(const IInterferenceFunctionStrategy *p_strategy);
    void calculateInCoherentIntensity();

};

#endif /* LAYERDECORATORDWBASIMULATION_H_ */
