// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/LocalMonodisperseApproximationStrategy.h
//! @brief     Defines class LocalMonodisperseApproximationStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_
#define LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_

#include "IInterferenceFunctionStrategy.h"

//! ?

class LocalMonodisperseApproximationStrategy : public IInterferenceFunctionStrategy
{
public:
    LocalMonodisperseApproximationStrategy(SimulationParameters sim_params);
    virtual ~LocalMonodisperseApproximationStrategy() {}

    virtual void init(const SafePointerVector<FormFactorInfo>& form_factor_infos,
            const SafePointerVector<IInterferenceFunction>& ifs);
    virtual double evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            double alpha_f) const;

    //! Calculates and returns a polarized form factor in DWBA
    virtual Eigen::Matrix2d evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
            double alpha_i, double alpha_f, double phi_f) const;
private:
    bool checkVectorSizes();
};

#endif /* LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_ */


