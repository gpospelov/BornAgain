// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions2D.h
//! @brief     Defines interface class IFTDistribution2D, and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FTDISTRIBUTIONS2D_H
#define FTDISTRIBUTIONS2D_H

#include "ICloneable.h"
#include "IDistribution2DSampler.h"
#include "INode.h"
#include "MathConstants.h"
#include "Integrator.h"

//! Interface for two-dimensional distributions in Fourier space.
//! @ingroup distribution_internal

class BA_CORE_API_ IFTDistribution2D : public ICloneable, public INode
{
public:
    IFTDistribution2D(double omega_x, double omega_y, double gamma = 0);
    IFTDistribution2D* clone() const = 0;

    void setGamma(double gamma) { m_gamma = gamma; }
    double gamma() const { return m_gamma; }

    double delta() const { return m_delta; }

    double omegaX() const { return m_omega_x; }
    double omegaY() const { return m_omega_y; }

    //! evaluate Fourier transformed distribution for q in X,Y coordinates
    //! the original distribution (in real space) is assumed to be normalized:
    //! total integral is equal to 1
    virtual double evaluate(double qx, double qy) const = 0;

#ifndef SWIG
    virtual std::unique_ptr<IDistribution2DSampler> createSampler() const = 0;
#endif

protected:
    double sumsq(double qx, double qy) const;

    void register_omega();
    void register_gamma();
    void init_parameters();

    double m_omega_x; //!< Half-width of the distribution along its x-axis in nanometers.
    double m_omega_y; //!< Half-width of the distribution along its y-axis in nanometers.
    //! Angle in direct space between first lattice vector and X-axis of distribution.
    double m_gamma;
    //! Angle in direct space between X- and Y-axis of distribution.
    double m_delta;
};

//! Two-dimensional Cauchy distribution in Fourier space;
//! corresponds to a normalized exp(-r) in real space,
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup distributionFT

class BA_CORE_API_ FTDistribution2DCauchy : public IFTDistribution2D
{
public:
    FTDistribution2DCauchy(double omega_x, double omega_y, double gamma = 0);

    FTDistribution2DCauchy* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif
};

//! Two-dimensional Gauss distribution in Fourier space;
//! corresponds to normalized exp(-r^2/2) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup distributionFT

class BA_CORE_API_ FTDistribution2DGauss : public IFTDistribution2D
{
public:
    FTDistribution2DGauss(double omega_x, double omega_y, double gamma = 0);

    FTDistribution2DGauss* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif
};

//! Two-dimensional gate distribution in Fourier space;
//! corresponds to normalized constant if r<1 (and 0 otherwise) in real space,
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup distributionFT

class BA_CORE_API_ FTDistribution2DGate : public IFTDistribution2D
{
public:
    FTDistribution2DGate(double omega_x, double omega_y, double gamma = 0);

    FTDistribution2DGate* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif
};

//! Two-dimensional cone distribution in Fourier space;
//! corresponds to 1-r if r<1 (and 0 otherwise) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup distributionFT

class BA_CORE_API_ FTDistribution2DCone : public IFTDistribution2D
{
public:
    FTDistribution2DCone(double omega_x, double omega_y, double gamma = 0);

    FTDistribution2DCone* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif

private:
    mutable RealIntegrator m_integrator;
};

//! Two-dimensional Voigt distribution in Fourier space;
//! corresponds to eta*Gauss + (1-eta)*Cauchy
//! @ingroup distributionFT

class BA_CORE_API_ FTDistribution2DVoigt : public IFTDistribution2D
{
public:
    FTDistribution2DVoigt(double omega_x, double omega_y, double eta, double gamma = 0);

    FTDistribution2DVoigt* clone() const final;
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
    double evaluate(double qx, double qy) const final;
    double eta() const { return m_eta; }
#ifndef SWIG
    std::unique_ptr<IDistribution2DSampler> createSampler() const final;
#endif

protected:
    double m_eta;
};

#endif // FTDISTRIBUTIONS2D_H
