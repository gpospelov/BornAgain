// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IsGISAXSMorphologyFileStrategy.h
//! @brief     Defines class IsGISAXSMorphologyFileStrategy.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXSMORPHOLOGYFILESTRATEGY_H_
#define ISGISAXSMORPHOLOGYFILESTRATEGY_H_

#include "Types.h"
#include "IInterferenceFunctionStrategy.h"


//! @class ISampleBuilder
//! @ingroup algorithms_internal
//! @brief Definition of interference function strategy that emulates the behaviour of
//! IsGISAXS for morphology files

class BA_CORE_API_ IsGISAXSMorphologyFileStrategy : public IInterferenceFunctionStrategy
{
public:
    IsGISAXSMorphologyFileStrategy(SimulationParameters sim_params);
    virtual ~IsGISAXSMorphologyFileStrategy() {}

    virtual void init(const SafePointerVector<FormFactorInfo>& form_factor_infos,
            const SafePointerVector<IInterferenceFunction>& ifs);

protected:
    //! Evaluates the intensity for given list of evaluated form factors
    virtual double evaluateForList(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin,
        const std::vector<complex_t> &ff_list) const;

private:
    void initPositions();
    bool checkVectorSizes();
    std::vector<double> m_x_positions;
    std::vector<double> m_y_positions;
    double m_win_x, m_win_y;
    //! Hann function
    double hannFunction(double x, double y) const;
};

#endif /* ISGISAXSMORPHOLOGYFILESTRATEGY_H_ */