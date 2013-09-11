// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IInterferenceFunctionStrategy.h
//! @brief     Defines class IInterferenceFunctionStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IINTERFERENCEFUNCTIONSTRATEGY_H_
#define IINTERFERENCEFUNCTIONSTRATEGY_H_

#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "Bin.h"
#include "SafePointerVector.h"
#include "LayerStrategyBuilder.h"
#include "FormFactorDWBAPol.h"

#include <vector>

class IInterferenceFunctionStrategy
{
public:
    IInterferenceFunctionStrategy(SimulationParameters sim_params)
        : m_sim_params(sim_params) {}
    virtual ~IInterferenceFunctionStrategy() {}
    virtual void init(const SafePointerVector<FormFactorInfo>&
                      form_factor_infos,
                      const SafePointerVector<IInterferenceFunction>& ifs);
    virtual double evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            Bin1D alpha_f_bin) const=0;
    //! Calculates and returns a polarized form factor in DWBA
    virtual Eigen::Matrix2d evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
            double alpha_i, Bin1D alpha_f_bin, Bin1D phi_f_bin) const=0;

protected:
    //! Returns mean form factor, possibly including their position information
    complex_t meanFormFactor(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            Bin1D alpha_f_bin, bool use_position=false) const;
    //! Returns mean squared form factor
    double meanSquaredFormFactor(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            Bin1D alpha_f_bin) const;
    //! Returns q-vector from k_i and the bin of k_f
    cvector_t getQ(const cvector_t& k_i, const Bin1DCVector& k_f_bin) const;
    SafePointerVector<FormFactorInfo> m_ff_infos; //!< form factor info
    SafePointerVector<IInterferenceFunction> m_ifs; //!< interference functions
    SimulationParameters m_sim_params; //!< simulation parameters
};

inline void IInterferenceFunctionStrategy::init(
        const SafePointerVector<FormFactorInfo>& form_factor_infos,
        const SafePointerVector<IInterferenceFunction>& ifs)
{
    m_ff_infos = form_factor_infos;
    m_ifs = ifs;
}

inline complex_t IInterferenceFunctionStrategy::meanFormFactor(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin, bool use_position) const
{
    complex_t result;
    for (SafePointerVector<FormFactorInfo>::const_iterator
             it=m_ff_infos.begin();
         it != m_ff_infos.end(); ++it) {
        complex_t ff_value =
            (*it)->mp_ff->evaluate(k_i, k_f_bin, alpha_f_bin);
        if (use_position) {
            cvector_t q = getQ(k_i, k_f_bin);
            complex_t phase = q.x()*(*it)->m_pos_x + q.y()*(*it)->m_pos_y;
            ff_value *= std::exp(complex_t(0.0, 1.0)*phase);
        }
        result += ff_value;
    }
    return result;
}

inline double IInterferenceFunctionStrategy::meanSquaredFormFactor(
    const cvector_t& k_i, const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    double result=0.0;
    for (SafePointerVector<FormFactorInfo>::const_iterator it=m_ff_infos.begin();
            it != m_ff_infos.end(); ++it) {
        complex_t ff_value = (*it)->mp_ff->evaluate(k_i, k_f_bin, alpha_f_bin);
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


