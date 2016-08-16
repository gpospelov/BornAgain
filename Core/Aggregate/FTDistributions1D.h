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

//! Interface for a one-dimensional distribution function,
//!   with evaluate(q) returning the Fourier transform, normalized so that evaluate(0)=1.
//! @ingroup algorithms_internal

class BA_CORE_API_ IFTDistribution1D : public IParameterized
{
public:
    IFTDistribution1D(double omega) : m_omega(omega) {}

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


//! One-dimensional Cauchy distribution in Fourier space;
//! corresponds to a normalized exp(-|x|) in real space.
//! @ingroup algorithms

class BA_CORE_API_ FTDistribution1DCauchy : public IFTDistribution1D
{
public:
    FTDistribution1DCauchy(double omega);
    FTDistribution1DCauchy* clone() const final { return new FTDistribution1DCauchy(m_omega); }
    double evaluate(double q) const final;
};


//! One-dimensional Gauss distribution in Fourier space;
//! corresponds to a normalized exp(-x^2) in real space.
//! @ingroup algorithms

class BA_CORE_API_ FTDistribution1DGauss : public IFTDistribution1D
{
public:
    FTDistribution1DGauss(double omega);
    FTDistribution1DGauss* clone() const final { return new FTDistribution1DGauss(m_omega); }
    double evaluate(double q) const final;
};


//! One-dimensional Gate distribution in Fourier space;
//! corresponds to a normalized constant if |x|<omega (and 0 otherwise) in real space.
//! @ingroup algorithms

class BA_CORE_API_ FTDistribution1DGate : public IFTDistribution1D
{
public:
    FTDistribution1DGate(double omega);
    FTDistribution1DGate* clone() const final { return new FTDistribution1DGate(m_omega); }
    double evaluate(double q) const final;
};


//! One-dimensional triangle distribution in Fourier space;
//! corresponds to a normalized 1-|x|/omega if |x|<omega (and 0 otherwise) in real space.
//! @ingroup algorithms

class BA_CORE_API_ FTDistribution1DTriangle : public IFTDistribution1D
{
public:
    FTDistribution1DTriangle(double omega);
    virtual ~FTDistribution1DTriangle() {}
    FTDistribution1DTriangle* clone() const final { return new FTDistribution1DTriangle(m_omega); }
    double evaluate(double q) const final;
};


//! One-dimensional triangle distribution in Fourier space;
//! corresponds to a normalized 1+cos(pi*x/omega) if |x|<omega (and 0 otherwise) in real space.
//! @ingroup algorithms

class BA_CORE_API_ FTDistribution1DCosine : public IFTDistribution1D
{
public:
    FTDistribution1DCosine(double omega);
    FTDistribution1DCosine* clone() const final { return new FTDistribution1DCosine(m_omega); }
    double evaluate(double q) const final;
};


//! One-dimensional pseudo-Voigt distribution in Fourier space;
//! corresponds to eta*Gauss + (1-eta)*Cauchy.
//! @ingroup algorithms

class BA_CORE_API_ FTDistribution1DVoigt : public IFTDistribution1D
{
public:
    FTDistribution1DVoigt(double omega, double eta);
    FTDistribution1DVoigt* clone() const final {
        return new FTDistribution1DVoigt(m_omega, m_eta); }
    double evaluate(double q) const final;
    double getEta() const { return m_eta;}
protected:
    virtual void init_parameters();
    double m_eta;
};

#endif // FTDISTRIBUTIONS1D_H
