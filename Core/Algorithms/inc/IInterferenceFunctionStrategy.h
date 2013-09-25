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
    double evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            Bin1D alpha_f_bin) const;
    //! Calculates a matrix valued intensity
    Eigen::Matrix2d evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin,
            Bin1D phi_f_bin) const;

protected:
    //! Evaluates the intensity for given list of evaluated form factors
    virtual double evaluateForList(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin,
            const std::vector<complex_t> &ff_list) const=0;
    //! Returns mean form factor, possibly including their position information
    complex_t meanFormFactor(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            Bin1D alpha_f_bin, bool use_position=false) const;
    //! Returns mean squared form factor
    double meanSquaredFormFactor(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const;
    //! Constructs one list of evaluated form factors to be used in subsequent
    //! calculations
    void calculateFormFactorList(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const;
    //! Constructs lists of evaluated form factors to be used in subsequent
    //! calculations
    void calculateFormFactorLists(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin, Bin1D phi_f_bin) const;
    //! Clears the cached form factor lists
    void clearFormFactorLists() const;
    //! Returns q-vector from k_i and the bin of k_f
    cvector_t getQ(const cvector_t& k_i, const Bin1DCVector& k_f_bin) const;
    SafePointerVector<FormFactorInfo> m_ff_infos; //!< form factor info
    SafePointerVector<IInterferenceFunction> m_ifs; //!< interference functions
    SimulationParameters m_sim_params; //!< simulation parameters
    //! cached form factor evaluations
    mutable std::vector<complex_t> m_ff00, m_ff01, m_ff10, m_ff11;
};

inline cvector_t IInterferenceFunctionStrategy::getQ(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin) const
{
    return k_i - k_f_bin.getMidPoint();
}

#endif /* IINTERFERENCEFUNCTIONSTRATEGY_H_ */


