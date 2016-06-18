// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/LayerStrategyBuilder.h
//! @brief     Declares classes LayerStrategyBuilder, FormFactorInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERSTRATEGYBUILDER_H
#define LAYERSTRATEGYBUILDER_H

#include "IMaterial.h"
#include "SafePointerVector.h"
#include "SimulationOptions.h"
#include <memory>

class FormFactorInfo;
class IInterferenceFunctionStrategy;
class Simulation;
class LayerSpecularInfo;


//! @class LayerStrategyBuilder
//! @ingroup algorithms_internal
//! @brief Methods to generate a simulation strategy for decorated Layer SimulationParameters

class BA_CORE_API_ LayerStrategyBuilder
{
public:
    LayerStrategyBuilder(
        const Layer& decorated_layer,
        const Simulation& simulation,
        const SimulationOptions& sim_params,
        size_t layout_index);

    virtual ~LayerStrategyBuilder();

    //! Sets reflection/transmission map for DWBA calculation
    void setRTInfo(const LayerSpecularInfo &specular_info);

    //! Creates a strategy object which is able to calculate the scattering for fixed k_f
    virtual IInterferenceFunctionStrategy *createStrategy();

protected:
    std::unique_ptr<Layer> mP_layer;                            //!< decorated layer
    std::unique_ptr<Simulation> mP_simulation;                  //!< simulation
    SimulationOptions m_sim_params;          //!< simulation parameters
    std::unique_ptr<LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA
    size_t m_layout_index; //!< index for the layout to be used in the layer

private:
    //! determines if the form factors need to be matrix valued
    bool requiresMatrixFFs() const;
    //! collect the formfactor info of all particles in the decoration and decorate
    //! these for DWBA when needed
    void collectFormFactorInfos();
    //! collect the interference function
    void collectInterferenceFunction();
    //! Creates formfactor info for single particle
    FormFactorInfo *createFormFactorInfo(const IParticle *particle,
                                         const IMaterial *p_ambient_material) const;

    //! Info about form factors
    SafePointerVector<FormFactorInfo> m_ff_infos;

    //! Interference function
    std::unique_ptr<IInterferenceFunction> mP_interference_function;
};

//! @class FormFactorInfo
//! @ingroup formfactors_internal
//! @brief The %FormFactorInfo holds information about particle position and abundance

class BA_CORE_API_ FormFactorInfo : public ICloneable
{
public:
    FormFactorInfo()
        : mp_ff(0), m_pos_x(0.0), m_pos_y(0.0), m_abundance(0.0) {}
    virtual ~FormFactorInfo();
    /* out-of-place implementation required due to IFormFactor */
    virtual FormFactorInfo *clone() const;
    IFormFactor *mp_ff;
    double m_pos_x, m_pos_y;
    double m_abundance;
};

#endif // LAYERSTRATEGYBUILDER_H
