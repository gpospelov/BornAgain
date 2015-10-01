// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/IFitStrategy.h
//! @brief     Defines interface class IFitStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFITSTRATEGY_H
#define IFITSTRATEGY_H

#include "INamed.h"
#include "Types.h"
#include "OutputData.h"
class FitKernel;

#include <string>
#include <vector>
#include <map>


//! @class IFitStrategy
//! @ingroup fitting_internal
//! @brief Interface to concrete fit strategy.
//!
//!  Concrete implementation should manipulate with fit parameters/data
//!  and then call minimizer.

class BA_CORE_API_ IFitStrategy : public INamed
{
public:
    IFitStrategy() : m_fit_kernel(0) {}
    IFitStrategy(const std::string& name) : INamed(name), m_fit_kernel(0) {}
    virtual IFitStrategy *clone() const = 0;

    virtual ~IFitStrategy(){}
    virtual void init(FitKernel *fit_suite) { m_fit_kernel = fit_suite; }
    virtual void execute() = 0;
protected:
    FitKernel *m_fit_kernel;
    IFitStrategy(const IFitStrategy &other) : INamed(other)
    {
        m_fit_kernel = other.m_fit_kernel;
    }

private:
    IFitStrategy& operator=(const IFitStrategy& );

};


//! @class FitStrategyDefault
//! @ingroup fitting
//! @brief Default fit strategy just let FitSuite to run it's minimization round

class BA_CORE_API_ FitStrategyDefault : public IFitStrategy
{
 public:
    FitStrategyDefault() : IFitStrategy("FitStrategyDefault") { }
    virtual IFitStrategy *clone() const { return new FitStrategyDefault(); }
    virtual void execute();
};


#endif // FITSTRATEGY_H


