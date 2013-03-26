// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/MultiLayerRoughnessDWBASimulation.h
//! @brief     Defines class MultiLayerRoughnessDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef MULTILAYERROUGHNESSDWBASIMULATION_H
#define MULTILAYERROUGHNESSDWBASIMULATION_H

#include "DWBASimulation.h"
#include <vector>

class MultiLayer;
#include "IDoubleToComplexFunction.h"

//! Calculation of diffuse reflection from multilayer with rough interfaces

class MultiLayerRoughnessDWBASimulation : public DWBASimulation
{
 public:
    MultiLayerRoughnessDWBASimulation(const MultiLayer *p_multi_layer);
    virtual ~MultiLayerRoughnessDWBASimulation();

    MultiLayerRoughnessDWBASimulation *clone() const
    {
        throw NotImplementedException(
            "MultiLayerRoughnessDWBASimulation::clone() -> "
            "Error: not implemented.");
    }

    virtual void run();

    // set T and R functions for given layer
    void setReflectionTransmissionFunction(
        size_t i_layer, const IDoubleToPairOfComplexMap &RT_function);

    // evaluate
    virtual double evaluate(const cvector_t &k_i, const cvector_t &k_f,
                            double alpha_i, double alpha_f);

 protected:
    complex_t get_refractive_term(size_t ilayer) const;
    complex_t get_sum4terms(size_t ilayer,
                            const cvector_t &k_i, const cvector_t &k_f,
                            double alpha_i, double alpha_f);

    std::vector<IDoubleToPairOfComplexMap *> mp_RT_function;
    MultiLayer *mp_multi_layer;
};

#endif // MULTILAYERROUGHNESSDWBASIMULATION_H
