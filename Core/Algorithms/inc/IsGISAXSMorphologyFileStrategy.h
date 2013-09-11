// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IsGISAXSMorphologyFileStrategy.h
//! @brief     Defines class IsGISAXSMorphologyFileStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
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

//! Definition of interference function strategy that emulates the behaviour of
//! IsGISAXS for morphology files

class IsGISAXSMorphologyFileStrategy : public IInterferenceFunctionStrategy
{
public:
    IsGISAXSMorphologyFileStrategy(SimulationParameters sim_params);
    virtual ~IsGISAXSMorphologyFileStrategy() {}

    virtual void init(const SafePointerVector<FormFactorInfo>& form_factor_infos,
            const SafePointerVector<IInterferenceFunction>& ifs);
    virtual double evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            Bin1D alpha_f_bin) const;

    //! Calculates and returns a polarized form factor in DWBA
    virtual Eigen::Matrix2d evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin,
            Bin1D phi_f_bin) const;
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


