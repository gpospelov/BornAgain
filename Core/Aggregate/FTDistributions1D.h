// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions1D.h
//! @brief     Defines interface class IFTDistribution1D, and children thereof
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FTDISTRIBUTIONS1D_H
#define FTDISTRIBUTIONS1D_H

#include "IParameterized.h"

// ************************************************************************** //
//! @class IFTDistribution1D
// ************************************************************************** //
//! @ingroup algorithms_internal
//! @brief Interface for 1 dimensional distributions in Fourier space

class BA_CORE_API_ IFTDistribution1D : public IParameterized
{
public:
    IFTDistribution1D(double omega) : m_omega(omega) {}
    virtual ~IFTDistribution1D() {}

    virtual IFTDistribution1D* clone() const=0;
    virtual double evaluate(double q) const=0;
    void setOmega(double omega) { m_omega = omega; }
    double getOmega() const { return m_omega; }

    friend std::ostream& operator<<(std::ostream& ostr, const IFTDistribution1D& m) {
        m.print(ostr); return ostr; }

protected:
    virtual void print(std::ostream& ostr) const;
    virtual void init_parameters();
    double m_omega;
};

// ************************************************************************** //
//! @class FTDistribution1DCauchy
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 1 dimensional Cauchy distribution in Fourier space.
//! Corresponds to a normalized exp(-|x|) in real space.

class BA_CORE_API_ FTDistribution1DCauchy : public IFTDistribution1D
{
public:
    FTDistribution1DCauchy(double omega);
    virtual ~FTDistribution1DCauchy() {}

    virtual FTDistribution1DCauchy* clone() const;

    virtual double evaluate(double q) const;
};

// ************************************************************************** //
//! @class FTDistribution1DGauss
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 1 dimensional Gauss distribution in Fourier space.
//! Corresponds to a normalized exp(-x^2) in real space.

class BA_CORE_API_ FTDistribution1DGauss : public IFTDistribution1D
{
public:
    FTDistribution1DGauss(double omega);
    virtual ~FTDistribution1DGauss() {}

    virtual FTDistribution1DGauss* clone() const;

    virtual double evaluate(double q) const;
};

// ************************************************************************** //
//! @class FTDistribution1DGate
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 1 dimensional Gate distribution in Fourier space.
//! Corresponds to a normalized constant if |x|<omega (and 0 otherwise) in real space.

class BA_CORE_API_ FTDistribution1DGate : public IFTDistribution1D
{
public:
    FTDistribution1DGate(double omega);
    virtual ~FTDistribution1DGate() {}

    virtual FTDistribution1DGate* clone() const;

    virtual double evaluate(double q) const;
};

// ************************************************************************** //
//! @class FTDistribution1DTriangle
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 1 dimensional triangle distribution in Fourier space.
//! Corresponds to a normalized 1-|x|/omega if |x|<omega (and 0 otherwise) in real space.

class BA_CORE_API_ FTDistribution1DTriangle : public IFTDistribution1D
{
public:
    FTDistribution1DTriangle(double omega);
    virtual ~FTDistribution1DTriangle() {}

    virtual FTDistribution1DTriangle* clone() const;

    virtual double evaluate(double q) const;
};

// ************************************************************************** //
//! @class FTDistribution1DCosine
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 1 dimensional triangle distribution in Fourier space.
//! Corresponds to a normalized 1+cos(pi*x/omega) if |x|<omega (and 0 otherwise) in real space.

class BA_CORE_API_ FTDistribution1DCosine : public IFTDistribution1D
{
public:
    FTDistribution1DCosine(double omega);
    virtual ~FTDistribution1DCosine() {}

    virtual FTDistribution1DCosine* clone() const;

    virtual double evaluate(double q) const;
};

// ************************************************************************** //
//! @class FTDistribution1DVoigt
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 1 dimensional Voigt distribution in Fourier space.
//! Corresponds to eta*Gauss + (1-eta)*Cauchy

class BA_CORE_API_ FTDistribution1DVoigt : public IFTDistribution1D
{
public:
    FTDistribution1DVoigt(double omega, double eta);
    virtual ~FTDistribution1DVoigt() {}

    virtual FTDistribution1DVoigt* clone() const;

    virtual double evaluate(double q) const;

    virtual double getEta() const { return m_eta;}

protected:
    virtual void init_parameters();
    double m_eta;
};

#endif // FTDISTRIBUTIONS1D_H
