// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/DecouplingApproximationStrategy.h
//! @brief     Defines class DecouplingApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECOUPLINGAPPROXIMATIONSTRATEGY_H_
#define DECOUPLINGAPPROXIMATIONSTRATEGY_H_

#include "Types.h"
#include "IInterferenceFunctionStrategy.h"

//! @class DecouplingApproximationStrategy
//! @ingroup algorithms_internal
//! @brief Strategy for implementing decoupling approximation

class BA_CORE_API_ DecouplingApproximationStrategy : public IInterferenceFunctionStrategy
{
public:
    DecouplingApproximationStrategy(SimulationParameters sim_params)
        : IInterferenceFunctionStrategy(sim_params)
    {
    }

    virtual ~DecouplingApproximationStrategy()
    {
    }

    void init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
              const IInterferenceFunction& iff);

protected:
    //! Evaluates the intensity for given list of evaluated form factors
    double evaluateForList(const SimulationElement& sim_element,
                           const std::vector<complex_t> &ff_list) const;

    //! Evaluates the intensity for given list of evaluated form factors
    //! in the presence of polarization of beam and detector
    double evaluateForMatrixList(const SimulationElement& sim_element,
                                 const MatrixFFVector &ff_list) const;

private:
    bool checkVectorSizes() const;
};

#endif /* DECOUPLINGAPPROXIMATIONSTRATEGY_H_ */
