#ifndef IINTERFERENCEFUNCTIONSTRATEGY_H_
#define IINTERFERENCEFUNCTIONSTRATEGY_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IInterferenceFunctionStrategy.h
//! @brief  Definition of IInterferenceFunctionStrategy class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 29, 2012

#include "Types.h"
#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "Bin.h"
#include "SafePointerVector.h"
#include "StrategyBuilder.h"

#include <vector>

class IInterferenceFunctionStrategy
{
public:
    IInterferenceFunctionStrategy(SimulationParameters sim_params)
        : m_sim_params(sim_params) {};
    virtual ~IInterferenceFunctionStrategy() {}
    virtual void init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
            const SafePointerVector<IInterferenceFunction> &ifs);
    virtual double evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const=0;
protected:
    //! calculate mean form factor, possibly including their position information
    complex_t meanFormFactor(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f, bool use_position=false) const;
    //! calculate mean squared form factor
    double meanSquaredFormFactor(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const;
    //! get q-vector from k_i and the bin of k_f
    cvector_t getQ(const cvector_t &k_i, const Bin1DCVector &k_f_bin) const;
    SafePointerVector<FormFactorInfo> m_ff_infos; //!< form factor info
    SafePointerVector<IInterferenceFunction> m_ifs; //!< interference functions
    SimulationParameters m_sim_params; //!< simulation parameters
};

inline void IInterferenceFunctionStrategy::init(
        const SafePointerVector<FormFactorInfo> &form_factor_infos,
        const SafePointerVector<IInterferenceFunction> &ifs)
{
    m_ff_infos = form_factor_infos;
    m_ifs = ifs;
}

inline complex_t IInterferenceFunctionStrategy::meanFormFactor(const cvector_t &k_i,
        const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f, bool use_position) const
{
    complex_t result;
    for (SafePointerVector<FormFactorInfo>::const_iterator it=m_ff_infos.begin();
            it != m_ff_infos.end(); ++it) {
        complex_t ff_value = (*it)->mp_ff->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
        if (use_position) {
            cvector_t q = getQ(k_i, k_f_bin);
            complex_t phase = q.x()*(*it)->m_pos_x + q.y()*(*it)->m_pos_y;
            ff_value *= std::exp(complex_t(0.0, 1.0)*phase);
        }
        result += ff_value;
    }
    return result;
}

inline double IInterferenceFunctionStrategy::meanSquaredFormFactor(const cvector_t &k_i,
        const Bin1DCVector &k_f_bin, double alpha_i, double alpha_f) const
{
    double result;
    for (SafePointerVector<FormFactorInfo>::const_iterator it=m_ff_infos.begin();
            it != m_ff_infos.end(); ++it) {
        complex_t ff_value = (*it)->mp_ff->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
        result += std::norm(ff_value);
    }
    return result;
}

inline cvector_t IInterferenceFunctionStrategy::getQ(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin) const
{
    return k_i - k_f_bin.getMidPoint();
}

#endif /* IINTERFERENCEFUNCTIONSTRATEGY_H_ */
