// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/LocalMonodisperseApproximationStrategy.h 
//! @brief     Defines class LocalMonodisperseApproximationStrategy.
//
// ************************************************************************** //

#ifndef LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_
#define LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_

#include "IInterferenceFunctionStrategy.h"

class LocalMonodisperseApproximationStrategy : public IInterferenceFunctionStrategy
{
public:
    LocalMonodisperseApproximationStrategy(SimulationParameters sim_params);
    virtual ~LocalMonodisperseApproximationStrategy() {}

    virtual void init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
            const SafePointerVector<IInterferenceFunction> &ifs);
    virtual double evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const;
private:
    bool checkVectorSizes();
};

#endif /* LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_ */
