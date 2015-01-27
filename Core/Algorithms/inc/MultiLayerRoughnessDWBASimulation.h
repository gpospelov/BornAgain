// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/MultiLayerRoughnessDWBASimulation.h
//! @brief     Defines class MultiLayerRoughnessDWBASimulation.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERROUGHNESSDWBASIMULATION_H
#define MULTILAYERROUGHNESSDWBASIMULATION_H

#include "DWBASimulation.h"
#include "LayerSpecularInfo.h"

#include <vector>

class MultiLayer;


//! @class MultiLayerRoughnessDWBASimulation
//! @ingroup algorithms_internal
//! @brief Calculation of diffuse reflection from multilayer with rough interfaces

class BA_CORE_API_ MultiLayerRoughnessDWBASimulation : public DWBASimulation
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

    //! Sets magnetic reflection/transmission info for specific layer
    void setSpecularInfo(size_t i_layer,
            const LayerSpecularInfo &specular_info);

    // evaluate
    virtual double evaluate(const cvector_t& k_i, const cvector_t& k_f,
                            double alpha_i, double alpha_f);

protected:
    virtual void runProtected();

    complex_t get_refractive_term(size_t ilayer) const;
    complex_t get_sum4terms(size_t ilayer,
                            const cvector_t& k_i, const cvector_t& k_f,
                            double alpha_f);

    MultiLayer *mp_multi_layer;
    std::vector<LayerSpecularInfo *> mp_specular_info_vector;
};

inline void MultiLayerRoughnessDWBASimulation::setSpecularInfo(size_t i_layer,
        const LayerSpecularInfo &specular_info)
{
    delete mp_specular_info_vector[i_layer];
    mp_specular_info_vector[i_layer] = specular_info.clone();
}

#endif // MULTILAYERROUGHNESSDWBASIMULATION_H