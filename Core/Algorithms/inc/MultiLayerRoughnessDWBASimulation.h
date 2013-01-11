#ifndef MULTILAYERROUGHNESSDWBASIMULATION_H
#define MULTILAYERROUGHNESSDWBASIMULATION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MultiLayerRoughnessDWBASimulation.h
//! @brief  Calculation of diffuse reflection from multilayer with rough interfaces
//! @author Scientific Computing Group at FRM II
//! @date   02.08.2012

#include "DWBASimulation.h"
#include <vector>

class MultiLayer;
#include "IDoubleToComplexFunction.h"

//- -------------------------------------------------------------------
//! @class MultiLayerRoughnessDWBASimulation
//! @brief Calculation of diffuse reflection from multilayer with rough interfaces
//- -------------------------------------------------------------------
class MultiLayerRoughnessDWBASimulation : public DWBASimulation
{
public:
    MultiLayerRoughnessDWBASimulation(const MultiLayer *p_multi_layer);
    virtual ~MultiLayerRoughnessDWBASimulation();

    MultiLayerRoughnessDWBASimulation *clone() const { throw NotImplementedException("MultiLayerRoughnessDWBASimulation::clone() -> Error: not implemented."); }

    virtual void run();

    // set T and R functions for given layer
    void setReflectionTransmissionFunction(size_t i_layer, const IDoubleToPairOfComplexMap &RT_function);

    // evaluate
    virtual double evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f);

protected:
    complex_t get_refractive_term(size_t ilayer) const;
    complex_t get_sum4terms(size_t ilayer, const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f);

    std::vector<IDoubleToPairOfComplexMap *> mp_RT_function;
    MultiLayer *mp_multi_layer;
};

#endif // MULTILAYERROUGHNESSDWBASIMULATION_H
