// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/LayerDecoratorDWBASimulation.h 
//! @brief     Defines class LayerDecoratorDWBASimulation.
//
// ************************************************************************** //

#ifndef LAYERDECORATORDWBASIMULATION_H_
#define LAYERDECORATORDWBASIMULATION_H_

#include "LayerDWBASimulation.h"
#include "DiffuseDWBASimulation.h"
#include "IInterferenceFunctionStrategy.h"

class LayerDecorator;

//- -------------------------------------------------------------------
//! @class LayerDecoratorDWBASimulation
//! @brief Calculates scattering cross sections in DWBA for a layer with particles in/on it
//- -------------------------------------------------------------------
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
