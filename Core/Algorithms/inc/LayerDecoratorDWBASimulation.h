#ifndef LAYERDECORATORDWBASIMULATION_H_
#define LAYERDECORATORDWBASIMULATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   LayerDecoratorDWBASimulation.h
//! @brief  Definition of LayerDecoratorDWBASimulation class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 25, 2012

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

    virtual void init(const Experiment &experiment);

    virtual void run();
protected:
    LayerDecorator *mp_layer_decorator;
    DiffuseDWBASimulation *mp_diffuseDWBA;
private:
    //! copy constructor and assignment operator are hidden
    LayerDecoratorDWBASimulation(const LayerDecoratorDWBASimulation &);
    LayerDecoratorDWBASimulation &operator=(const LayerDecoratorDWBASimulation &);

    IInterferenceFunctionStrategy *createAndInitStrategy() const;
    std::vector<IFormFactor *> createDWBAFormFactors() const;
    void calculateCoherentIntensity(const IInterferenceFunctionStrategy *p_strategy);
    void calculateInCoherentIntensity();

};

#endif /* LAYERDECORATORDWBASIMULATION_H_ */
