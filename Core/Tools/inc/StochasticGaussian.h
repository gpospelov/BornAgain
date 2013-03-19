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
//! @file      Tools/StochasticGaussian.h 
//! @brief     Defines class StochasticGaussian.
//
// ************************************************************************** //

#ifndef STOCHASTICGAUSSIAN_H
#define STOCHASTICGAUSSIAN_H

#include "IStochasticParameter.h"
#include <cmath>

class StochasticDoubleGaussian : public StochasticParameter<double>
{
public:
    StochasticDoubleGaussian(double average, double std_dev);
    ~StochasticDoubleGaussian();
    virtual StochasticDoubleGaussian *clone() const;

    virtual void setToRandom();
    virtual double probabilityDensity(double value) const;

    double getStdDev() const { return m_std_dev; }

    virtual double getFWHM() const { return 2.*m_std_dev*std::sqrt(2.*std::log(2.)); }

private:
    double m_std_dev;
};

#endif // STOCHASTICGAUSSIAN_H
