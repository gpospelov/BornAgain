// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/FTDistributions.h
//! @brief     Defines classes IFTDistribution1D, IFTDistribution2D,
//!              FTDistribution2DCauchy
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FTDISTRIBUTIONS_H_
#define FTDISTRIBUTIONS_H_

#include "IParameterized.h"
#include <cmath>

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
protected:
    virtual void init_parameters();
    double m_omega;
};

//! @class FTDistribution1DCauchy
//! @ingroup algorithms
//! @brief 1 dimensional Cauchy distribution in Fourier space
//! corresponds to exp(-r) in real space

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
//! @brief 1 dimensional Gauss distribution in Fourier space
//! corresponds to exp(-r^2) in real space

class BA_CORE_API_ FTDistribution1DGauss : public IFTDistribution1D
{
public:
    FTDistribution1DGauss(double omega);
    virtual ~FTDistribution1DGauss() {}

    virtual FTDistribution1DGauss *clone() const;

    virtual double evaluate(double q) const;
};


//! @class FTDistribution1DVoigt
//! @ingroup algorithms
//! @brief 1 dimensional Voigt distribution in Fourier space
//! Corresponds to eta*Gauss + (1-eta)*Cauchy

class BA_CORE_API_ FTDistribution1DVoigt : public IFTDistribution1D
{
public:
    FTDistribution1DVoigt(double omega, double eta);
    virtual ~FTDistribution1DVoigt() {}

    virtual FTDistribution1DVoigt *clone() const;

    virtual double evaluate(double q) const;

protected:
    virtual void init_parameters();
    double m_eta;
};


//! @class IFTDistribution2D
//! @ingroup algorithms_internal
//! @brief Interface for 2 dimensional distributions in Fourier space
class BA_CORE_API_ IFTDistribution2D : public IParameterized
{
public:
    IFTDistribution2D(double coherence_length_x, double coherence_length_y)
        : m_coherence_length_x(coherence_length_x)
        , m_coherence_length_y(coherence_length_y)
        , m_gamma(0.0)
        , m_delta(M_PI/2.0) {}
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

    //! evaluate IF for q in X,Y coordinates
    //! A common factor of 2*pi*m_coherence_length_x*m_coherence_length_y is
    //! applied by the caller if needed
    virtual double evaluate(double qx, double qy) const=0;

    //! transform back to a*, b* basis:
    void transformToStarBasis(double qX, double qY,
            double alpha, double a, double b, double& qa, double& qb) const;

protected:
    virtual void init_parameters();
    double m_coherence_length_x;
    double m_coherence_length_y;
    double m_gamma;
    double m_delta;
};


//! @class FTDistribution2DCauchy
//! @ingroup algorithms
//! @brief 2 dimensional Cauchy distribution in Fourier space
//! corresponds to exp(-r) in real space

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
//! @brief 2 dimensional Gauss distribution in Fourier space
//! corresponds to exp(-r^2) in real space

class BA_CORE_API_ FTDistribution2DGauss : public IFTDistribution2D
{
public:
    FTDistribution2DGauss(double coherence_length_x, double coherence_length_y);
    virtual ~FTDistribution2DGauss() {}

    virtual FTDistribution2DGauss *clone() const;

    virtual double evaluate(double qx, double qy) const;
};


//! @class FTDistribution2DVoigt
//! @ingroup algorithms
//! @brief 2 dimensional Voigt distribution in Fourier space
//! Corresponds to eta*Gauss + (1-eta)*Cauchy

class BA_CORE_API_ FTDistribution2DVoigt : public IFTDistribution2D
{
public:
    FTDistribution2DVoigt(double coherence_length_x, double coherence_length_y,
            double eta);
    virtual ~FTDistribution2DVoigt() {}

    virtual FTDistribution2DVoigt *clone() const;

    virtual double evaluate(double qx, double qy) const;

protected:
    virtual void init_parameters();
    double m_eta;
};

#endif /* FTDISTRIBUTIONS_H_ */


