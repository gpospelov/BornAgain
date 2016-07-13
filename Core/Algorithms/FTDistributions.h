// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/FTDistributions.h
//! @brief     Declares classes IFTDistribution1D, IFTDistribution2D,
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FTDISTRIBUTIONS_H
#define FTDISTRIBUTIONS_H

#include "IParameterized.h"
#include "Units.h"
#include "Numeric.h"


//! @class IFTDistribution1D
//! @ingroup algorithms_internal
//! @brief Interface for 1 dimensional distributions in Fourier space
class BA_CORE_API_ IFTDistribution1D : public IParameterized
{
public:
    IFTDistribution1D(double omega) : m_omega(omega) {}
    virtual ~IFTDistribution1D() {}

    virtual IFTDistribution1D *clone() const=0;
    virtual double evaluate(double q) const=0;
    void setOmega(double omega) { m_omega = omega; }
    double getOmega() const { return m_omega; }

    friend std::ostream& operator<<(std::ostream& ostr, const IFTDistribution1D& m)
    { m.print(ostr); return ostr; }

protected:
    virtual void print(std::ostream& ostr) const;
    virtual void init_parameters();
    double m_omega;
};

//! @class FTDistribution1DCauchy
//! @ingroup algorithms
//! @brief 1 dimensional Cauchy distribution in Fourier space.
//! Corresponds to a normalized exp(-|x|) in real space
class BA_CORE_API_ FTDistribution1DCauchy : public IFTDistribution1D
{
public:
    FTDistribution1DCauchy(double omega);
    virtual ~FTDistribution1DCauchy() {}

    virtual FTDistribution1DCauchy *clone() const;

    virtual double evaluate(double q) const;
};

//! @class FTDistribution1DGauss
//! @ingroup algorithms
//! @brief 1 dimensional Gauss distribution in Fourier space.
//! Corresponds to a normalized exp(-x^2) in real space
class BA_CORE_API_ FTDistribution1DGauss : public IFTDistribution1D
{
public:
    FTDistribution1DGauss(double omega);
    virtual ~FTDistribution1DGauss() {}

    virtual FTDistribution1DGauss *clone() const;

    virtual double evaluate(double q) const;
};

//! @class FTDistribution1DGate
//! @ingroup algorithms
//! @brief 1 dimensional Gate distribution in Fourier space.
//! Corresponds to a normalized constant if |x|<omega (and 0 otherwise)
//! in real space
class BA_CORE_API_ FTDistribution1DGate : public IFTDistribution1D
{
public:
    FTDistribution1DGate(double omega);
    virtual ~FTDistribution1DGate() {}

    virtual FTDistribution1DGate *clone() const;

    virtual double evaluate(double q) const;
};

//! @class FTDistribution1DTriangle
//! @ingroup algorithms
//! @brief 1 dimensional triangle distribution in Fourier space.
//! Corresponds to a normalized 1-|x|/omega if |x|<omega (and 0 otherwise)
//! in real space
class BA_CORE_API_ FTDistribution1DTriangle : public IFTDistribution1D
{
public:
    FTDistribution1DTriangle(double omega);
    virtual ~FTDistribution1DTriangle() {}

    virtual FTDistribution1DTriangle *clone() const;

    virtual double evaluate(double q) const;
};

//! @class FTDistribution1DCosine
//! @ingroup algorithms
//! @brief 1 dimensional triangle distribution in Fourier space.
//! Corresponds to a normalized 1+cos(pi*x/omega) if |x|<omega (and 0 otherwise)
//! in real space
class BA_CORE_API_ FTDistribution1DCosine : public IFTDistribution1D
{
public:
    FTDistribution1DCosine(double omega);
    virtual ~FTDistribution1DCosine() {}

    virtual FTDistribution1DCosine *clone() const;

    virtual double evaluate(double q) const;
};

//! @class FTDistribution1DVoigt
//! @ingroup algorithms
//! @brief 1 dimensional Voigt distribution in Fourier space.
//! Corresponds to eta*Gauss + (1-eta)*Cauchy
class BA_CORE_API_ FTDistribution1DVoigt : public IFTDistribution1D
{
public:
    FTDistribution1DVoigt(double omega, double eta);
    virtual ~FTDistribution1DVoigt() {}

    virtual FTDistribution1DVoigt *clone() const;

    virtual double evaluate(double q) const;

    virtual double getEta() const { return m_eta;}

protected:
    virtual void init_parameters();
    double m_eta;
};

//! @class IFTDistribution2D
//! @ingroup algorithms_internal
//! @brief Interface for 2 dimensional distributions in Fourier space.
class BA_CORE_API_ IFTDistribution2D : public IParameterized
{
public:
    IFTDistribution2D(double coherence_length_x, double coherence_length_y)
        : m_coherence_length_x(coherence_length_x)
        , m_coherence_length_y(coherence_length_y)
        , m_gamma(0.0)
        , m_delta(Units::PI/2.0) {}
    virtual ~IFTDistribution2D() {}

    virtual IFTDistribution2D *clone() const=0;

    // set angle between first lattice vector and X-axis of distribution (both in direct space)
    void setGamma(double gamma) { m_gamma = gamma; }

    // get angle between first lattice vector and X-axis of distribution (both in direct space)
    double getGamma() const { return m_gamma; }

    // get angle between X- and Y-axis of distribution (in direct space)
    double getDelta() const { return m_delta; }

    // get coherence length in X-direction
    double getCoherenceLengthX() const { return m_coherence_length_x; }

    // get coherence length in Y-direction
    double getCoherenceLengthY() const { return m_coherence_length_y; }

    //! evaluate Fourier transformed distribution for q in X,Y coordinates
    //! the original distribution (in real space) is assumed to be normalized:
    //! total integral is equal to 1
    virtual double evaluate(double qx, double qy) const=0;

    friend std::ostream& operator<<(std::ostream& ostr, const IFTDistribution2D& m)
    { m.print(ostr); return ostr; }

protected:
    virtual void print(std::ostream& ostr) const;
    virtual void init_parameters();
    double m_coherence_length_x;
    double m_coherence_length_y;
    double m_gamma;
    double m_delta;
};

//! @class FTDistribution2DCauchy
//! @ingroup algorithms
//! @brief 2 dimensional Cauchy distribution in Fourier space.
//! Corresponds to a normalized exp(-r) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$
class BA_CORE_API_ FTDistribution2DCauchy : public IFTDistribution2D
{
public:
    FTDistribution2DCauchy(double coherence_length_x, double coherence_length_y);
    virtual ~FTDistribution2DCauchy() {}

    virtual FTDistribution2DCauchy *clone() const;

    virtual double evaluate(double qx, double qy) const;
};

//! @class FTDistribution2DGauss
//! @ingroup algorithms
//! @brief 2 dimensional Gauss distribution in Fourier space.
//! Corresponds to normalized exp(-r^2/2) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$
class BA_CORE_API_ FTDistribution2DGauss : public IFTDistribution2D
{
public:
    FTDistribution2DGauss(double coherence_length_x, double coherence_length_y);
    virtual ~FTDistribution2DGauss() {}

    virtual FTDistribution2DGauss *clone() const;

    virtual double evaluate(double qx, double qy) const;
};

//! @class FTDistribution2DGate
//! @ingroup algorithms
//! @brief 2 dimensional gate distribution in Fourier space
//! Corresponds to normalized constant if r<1 (and 0 otherwise) in real space.
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$
class BA_CORE_API_ FTDistribution2DGate : public IFTDistribution2D
{
public:
    FTDistribution2DGate(double coherence_length_x, double coherence_length_y);
    virtual ~FTDistribution2DGate() {}

    virtual FTDistribution2DGate *clone() const;

    virtual double evaluate(double qx, double qy) const;
};

//! @class FTDistribution2DCone
//! @ingroup algorithms
//! @brief 2 dimensional cone distribution in Fourier space.
//! Corresponds to 1-r if r<1 (and 0 otherwise) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$
class BA_CORE_API_ FTDistribution2DCone : public IFTDistribution2D
{
public:
    FTDistribution2DCone(double coherence_length_x, double coherence_length_y);
    virtual ~FTDistribution2DCone() {}

    virtual FTDistribution2DCone *clone() const;

    virtual double evaluate(double qx, double qy) const;

private:
    //! second part of the integrand:
    //! \f$u^2\cdot J_0(u)\f$
    double coneIntegrand2(double value) const;
};

//! @class FTDistribution2DVoigt
//! @ingroup algorithms
//! @brief 2 dimensional Voigt distribution in Fourier space.
//! Corresponds to eta*Gauss + (1-eta)*Cauchy
class BA_CORE_API_ FTDistribution2DVoigt : public IFTDistribution2D
{
public:
    FTDistribution2DVoigt(double coherence_length_x, double coherence_length_y,
            double eta);
    virtual ~FTDistribution2DVoigt() {}

    virtual FTDistribution2DVoigt *clone() const;

    virtual double evaluate(double qx, double qy) const;

    virtual double getEta() const { return m_eta;}

protected:
    virtual void init_parameters();
    double m_eta;
};

#endif // FTDISTRIBUTIONS_H
