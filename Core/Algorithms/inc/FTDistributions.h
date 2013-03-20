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

#include "ParameterPool.h"
#include <cmath>

class IFTDistribution1D
{
public:
    IFTDistribution1D(double omega) : m_omega(omega) {}
    virtual ~IFTDistribution1D() {}

    virtual double evaluate(double q) const=0;
protected:
    double m_omega;
};

class IFTDistribution2D : public IParameterized
{
public:
    IFTDistribution2D(double omega_x, double omega_y) : m_omega_x(omega_x), m_omega_y(omega_y),
        m_gamma(0.0), m_delta(M_PI/2.0) {}
    virtual ~IFTDistribution2D() {}

    virtual IFTDistribution2D *clone() const=0;

    // set angle between first lattice vector and X-axis of distribution (both in direct space)
    void setGamma(double gamma) { m_gamma = gamma; }

    // get angle between first lattice vector and X-axis of distribution (both in direct space)
    double getGamma() const { return m_gamma; }

    // get angle between X- and Y-axis of distribution (in direct space)
    double getDelta() const { return m_delta; }

    //! evaluate IF for q in X,Y coordinates
    virtual double evaluate(double qx, double qy) const=0;

    //! transform back to a*, b* basis:
    virtual void transformToStarBasis(double qX, double qY,
            double alpha, double a, double b, double &qa, double &qb) const=0;
protected:
    double m_omega_x;
    double m_omega_y;
    double m_gamma;
    double m_delta;
};

class FTDistribution2DCauchy : public IFTDistribution2D
{
public:
    FTDistribution2DCauchy(double omega_x, double omega_y);
    virtual ~FTDistribution2DCauchy() {}

    virtual FTDistribution2DCauchy *clone() const;

    virtual double evaluate(double qx, double qy) const;

    virtual void transformToStarBasis(double qX, double qY,
            double alpha, double a, double b, double &qa, double &qb) const;
protected:
    virtual void init_parameters();
};

#endif /* FTDISTRIBUTIONS_H_ */
