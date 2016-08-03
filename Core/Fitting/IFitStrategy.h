// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IFitStrategy.h
//! @brief     Declares interface class IFitStrategy, and class FitStrategyDefault
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

#include "INamed.h" // inheriting from

class FitKernel;

//! @class IFitStrategy
//! @ingroup fitting_internal
//! @brief Interface to concrete fit strategy.
//!
//!  Concrete implementation should manipulate with fit parameters/data and then call minimizer.

class BA_CORE_API_ IFitStrategy : public INamed
{
public:
    IFitStrategy();
    IFitStrategy(const std::string& name);
    virtual IFitStrategy* clone() const = 0;

    virtual ~IFitStrategy() {};
    virtual void init(FitKernel* fit_suite);
    virtual void execute() = 0;

    friend std::ostream &operator<<(std::ostream &ostr, const IFitStrategy &m)
    {
        m.print(ostr);
        return ostr;
    }

protected:
    virtual void print(std::ostream &ostr) const;

    FitKernel* m_kernel;
    IFitStrategy(const IFitStrategy &other);

private:
    IFitStrategy& operator=(const IFitStrategy& );
};


//! @class FitStrategyDefault
//! @ingroup fitting
//! @brief Default fit strategy just let FitSuite to run it's minimization round

class BA_CORE_API_ FitStrategyDefault : public IFitStrategy
{
 public:
    FitStrategyDefault();
    virtual IFitStrategy* clone() const;
    virtual void execute();
};

#endif // IFITSTRATEGY_H
