#ifndef STRATEGYBUILDER_H_
#define STRATEGYBUILDER_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   LayerDecoratorStrategyBuilder.h
//! @brief  Definition of LayerDecoratorStrategyBuilder class
//! @author Scientific Computing Group at FRM II
//! @date   Jan 24, 2013

#include "SimulationParameters.h"
#include "SafePointerVector.h"
#include "ICloneable.h"
#include "Types.h"

class FormFactorInfo;
class IInterferenceFunction;
class IInterferenceFunctionStrategy;
class LayerDecorator;
class Experiment;
class IDoubleToPairOfComplexMap;
class ParticleInfo;
class IFormFactor;

//- -------------------------------------------------------------------
//! @class LayerDecoratorStrategyBuilder
//! @brief Definition of methods to generate a simulation strategy from
//! a LayerDecorator and SimulationParameters
//- -------------------------------------------------------------------
class LayerDecoratorStrategyBuilder
{
public:
    LayerDecoratorStrategyBuilder(const LayerDecorator &decorated_layer,
            const Experiment &experiment, const SimulationParameters &sim_params);
    virtual ~LayerDecoratorStrategyBuilder();

    //! set R and T coefficient map for DWBA simulation
    void setReflectionTransmissionFunction(const IDoubleToPairOfComplexMap &rt_map);

    //! create a strategy object which is able to calculate the scattering for fixed k_f
    virtual IInterferenceFunctionStrategy *createStrategy();
protected:
    LayerDecorator *mp_layer_decorator;         //!< decorated layer
    Experiment *mp_experiment;                  //!< experiment
    SimulationParameters m_sim_params;          //!< simulation parameters
    IDoubleToPairOfComplexMap *mp_RT_function;  //!< R and T coefficients for DWBA
private:
    //! collect the formfactor info of all particles in the decoration and decorate
    //! these for DWBA when needed
    void collectFormFactorInfos();
    //! collect the interference functions
    void collectInterferenceFunctions();
    //! retrieve wavelength from experiment
    double getWavelength();
    //! create formfactor info for single particle
    FormFactorInfo *createFormFactorInfo(const ParticleInfo *p_particle_info,
            complex_t n_ambient_refractive_index, complex_t factor) const;

    SafePointerVector<FormFactorInfo> m_ff_infos;
    SafePointerVector<IInterferenceFunction> m_ifs;
};

class FormFactorInfo : public ICloneable
{
public:
    FormFactorInfo();
    ~FormFactorInfo();
    virtual FormFactorInfo *clone() const;
    IFormFactor *mp_ff;
    double m_pos_x, m_pos_y;
    double m_abundance;
};

#endif /* STRATEGYBUILDER_H_ */
