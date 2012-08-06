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

    virtual void run();

    // set T and R functions for given layer
    void setTAndRFunctions(int i, const IDoubleToComplexFunction &T_function, const IDoubleToComplexFunction &R_function);

    // evaluate
    virtual double evaluate(kvector_t k_i, kvector_t k_f);

protected:
    MultiLayerRoughnessDWBASimulation(const MultiLayerRoughnessDWBASimulation &);
    MultiLayerRoughnessDWBASimulation &operator=(const MultiLayerRoughnessDWBASimulation &);

    complex_t get_refractive_term(int ilayer);
    complex_t get_sum4terms(int ilayer, kvector_t k_i, kvector_t k_f);

    std::vector<IDoubleToComplexFunction *> mp_T_function;
    std::vector<IDoubleToComplexFunction *> mp_R_function;

    MultiLayer *mp_multi_layer;

};

#endif // MULTILAYERROUGHNESSDWBASIMULATION_H
