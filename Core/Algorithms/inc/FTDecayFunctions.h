// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/FTDecayFunctions.h
//! @brief     Defines classes IFTDecayFunction1D, IFTDecayFunction2D,
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FTDECAYFUNCTIONS_H_
#define FTDECAYFUNCTIONS_H_

#include "IParameterized.h"
#include "Units.h"
#include "Numeric.h"


//! @class IFTDecayFunction1D
//! @ingroup algorithms_internal
//! @brief Interface for 1 dimensional decay function in reciprocal space
class BA_CORE_API_ IFTDecayFunction1D : public IParameterized
{
public:
    IFTDecayFunction1D(double omega) : m_omega(omega) {}
    virtual ~IFTDecayFunction1D() {}

    virtual IFTDecayFunction1D *clone() const=0;
    virtual double evaluate(double q) const=0;
    void setOmega(double omega) { m_omega = omega; }
    double getOmega() const { return m_omega; }

    friend std::ostream& operator<<(std::ostream& ostr, const IFTDecayFunction1D& m)
    { m.print(ostr); return ostr; }

protected:
    virtual void print(std::ostream& ostr) const;
    virtual void init_parameters();
    double m_omega;
};

//! @class FTDecayFunction1DCauchy
//! @ingroup algorithms
//! @brief 1 dimensional Cauchy decay function in reciprocal space.
//! Corresponds to exp(-|x|/omega) in real space
class BA_CORE_API_ FTDecayFunction1DCauchy : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DCauchy(double omega);
    virtual ~FTDecayFunction1DCauchy() {}

    virtual FTDecayFunction1DCauchy *clone() const;

    virtual double evaluate(double q) const;
};

//! @class FTDecayFunction1DGauss
//! @ingroup algorithms
//! @brief 1 dimensional Gauss decay function in reciprocal space.
//! Corresponds to exp[-x^2/(2*omega^2)] in real space
class BA_CORE_API_ FTDecayFunction1DGauss : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DGauss(double omega);
    virtual ~FTDecayFunction1DGauss() {}

    virtual FTDecayFunction1DGauss *clone() const;

    virtual double evaluate(double q) const;
};

//! @class FTDecayFunction1DTriangle
//! @ingroup algorithms
//! @brief 1 dimensional triangle decay function in reciprocal space.
//! Corresponds to 1-|x|/omega if |x|<omega (and 0 otherwise)
//! in real space
class BA_CORE_API_ FTDecayFunction1DTriangle : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DTriangle(double omega);
    virtual ~FTDecayFunction1DTriangle() {}

    virtual FTDecayFunction1DTriangle *clone() const;

    virtual double evaluate(double q) const;
};


//! @class FTDecayFunction1DVoigt
//! @ingroup algorithms
//! @brief 1 dimensional Voigt decay function in reciprocal space.
//! Corresponds to eta*Gauss + (1-eta)*Cauchy
class BA_CORE_API_ FTDecayFunction1DVoigt : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DVoigt(double omega, double eta);
    virtual ~FTDecayFunction1DVoigt() {}

    virtual FTDecayFunction1DVoigt *clone() const;

    virtual double evaluate(double q) const;

    virtual double getEta() const { return m_eta;}

protected:
    virtual void init_parameters();
    double m_eta;
};

/* The commented decay functions give negative values in parts of the reciprocal space
 * From the physical perspective, only the exponential decay is possible (Cauchy), but
 * we left the Gaussian, Triangle and Voigt functions as a choice to experiment (these always give
 * positive values in reciprocal space)

//! @class FTDecayFunction1DGate
//! @ingroup algorithms
//! @brief 1 dimensional Gate decay function in reciprocal space.
//! Corresponds to the constant 1 if |x|<omega (and 0 otherwise)
//! in real space
class BA_CORE_API_ FTDecayFunction1DGate : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DGate(double omega);
    virtual ~FTDecayFunction1DGate() {}

    virtual FTDecayFunction1DGate *clone() const;

    virtual double evaluate(double q) const;
};


//! @class FTDecayFunction1DCosine
//! @ingroup algorithms
//! @brief 1 dimensional triangle decay function in reciprocal space.
//! Corresponds to a  [1+cos(pi*x/omega)]/2 if |x|<omega (and 0 otherwise)
//! in real space
class BA_CORE_API_ FTDecayFunction1DCosine : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DCosine(double omega);
    virtual ~FTDecayFunction1DCosine() {}

    virtual FTDecayFunction1DCosine *clone() const;

    virtual double evaluate(double q) const;
};
*/

#endif /* FTDECAYFUNCTIONS_H_ */
