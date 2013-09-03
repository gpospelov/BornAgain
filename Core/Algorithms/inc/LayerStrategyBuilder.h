// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/LayerStrategyBuilder.h
//! @brief     Defines classes LayerStrategyBuilder, FormFactorInfo.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERSTRATEGYBUILDER_H_
#define LAYERSTRATEGYBUILDER_H_

#include "SimulationParameters.h"
#include "SafePointerVector.h"
#include "ICloneable.h"
#include "Types.h"
#include "IMaterial.h"

class FormFactorInfo;
class IInterferenceFunction;
class IInterferenceFunctionStrategy;
class Layer;
class Simulation;
class IDoubleToPairOfComplexMap;
class ParticleInfo;
class IFormFactor;
class LayerSpecularInfo;

//! Methods to generate a simulation strategy for decorated Layer SimulationParameters

class LayerStrategyBuilder
{
public:
    LayerStrategyBuilder(
        const Layer& decorated_layer,
        const Simulation& simulation,
        const SimulationParameters& sim_params);

    virtual ~LayerStrategyBuilder();

    //! Sets reflection/transmission map for scalar DWBA simulation
    void setRTInfo(const IDoubleToPairOfComplexMap& rt_map);

    //! Sets reflection/transmission map for DWBA calculation
    void setRTInfo(const LayerSpecularInfo &specular_info);

    //! Creates a strategy object which is able to calculate the scattering for fixed k_f
    virtual IInterferenceFunctionStrategy *createStrategy();

protected:
    Layer *mp_layer;                            //!< decorated layer
    Simulation *mp_simulation;                  //!< simulation
    SimulationParameters m_sim_params;          //!< simulation parameters
    IDoubleToPairOfComplexMap *mp_RT_function;  //!< R and T coefficients for DWBA
    LayerSpecularInfo *mp_specular_info; //!< R and T coefficients for DWBA

private:
    //! collect the formfactor info of all particles in the decoration and decorate
    //! these for DWBA when needed
    void collectFormFactorInfos();
    //! collect the interference functions
    void collectInterferenceFunctions();
    //! retrieve wavelength from simulation
    double getWavelength();
    //! Creates formfactor info for single particle
    FormFactorInfo *createFormFactorInfo(
        const ParticleInfo *p_particle_info,
        const IMaterial *p_ambient_material,
        complex_t factor) const;
    //! Creates formfactor info for single particle in presence of polarization
    FormFactorInfo *createFormFactorInfoPol(
        const ParticleInfo *p_particle_info,
        const IMaterial *p_ambient_material,
        complex_t factor) const;

    SafePointerVector<FormFactorInfo> m_ff_infos;
    SafePointerVector<IInterferenceFunction> m_ifs;
};


class FormFactorInfo : public ICloneable
{
public:
    FormFactorInfo()
        : mp_ff(0), m_pos_x(0.0), m_pos_y(0.0), m_abundance(0.0) {}
    ~FormFactorInfo();
    /* out-of-place implementation required due to IFormFactor */
    virtual FormFactorInfo *clone() const;
    IFormFactor *mp_ff;
    double m_pos_x, m_pos_y;
    double m_abundance;
};

#endif /* LAYERSTRATEGYBUILDER_H_ */


