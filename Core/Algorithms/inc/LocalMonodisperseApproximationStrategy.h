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


//! @class LocalMonodisperseApproximationStrategy
//! @ingroup algorithms_internal
//! @brief Strategy which implements local monodisperse approximation.

class BA_CORE_API_ LocalMonodisperseApproximationStrategy :
                                      public IInterferenceFunctionStrategy
{
public:
    LocalMonodisperseApproximationStrategy(SimulationParameters sim_params);
    virtual ~LocalMonodisperseApproximationStrategy() {}

    virtual void init(const SafePointerVector<FormFactorInfo>& form_factor_infos,
            const SafePointerVector<IInterferenceFunction>& ifs);

protected:
    //! Evaluates the intensity for given list of evaluated form factors
    virtual double evaluateForList(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, const std::vector<complex_t> &ff_list) const;

private:
    bool checkVectorSizes();
};

#endif /* LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_ */


