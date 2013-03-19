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
//! @file      Algorithms/FTDistributions.cpp 
//! @brief     Implements class FTDistributions.
//
// ************************************************************************** //

#include "FTDistributions.h"

FTDistribution2DCauchy::FTDistribution2DCauchy(double omega_x, double omega_y)
: IFTDistribution2D(omega_x, omega_y)
{
    setName("2DDistributionCauchy");
    init_parameters();
}

FTDistribution2DCauchy* FTDistribution2DCauchy::clone() const
{
    FTDistribution2DCauchy *p_clone = new FTDistribution2DCauchy(m_omega_x, m_omega_y);
    p_clone->setGamma(m_gamma);
    return p_clone;
}

double FTDistribution2DCauchy::evaluate(double qx, double qy) const
{
    double sum_sq = qx*qx*m_omega_x*m_omega_x + qy*qy*m_omega_y*m_omega_y;
    return std::pow(1.0 + sum_sq, -1.5);
}

void FTDistribution2DCauchy::transformToStarBasis(double qX, double qY,
        double alpha, double a, double b, double& qa, double& qb) const
{
    double prefactor = 1.0/(2.0*M_PI); // divide by sin(m_delta) for unnormalized X*,Y* basis
    qa = a*prefactor*( std::sin(m_gamma+m_delta)*qX - std::sin(m_gamma)*qY );
    qb = b*prefactor*( -std::sin(alpha-m_gamma-m_delta)*qX + std::sin(alpha-m_gamma)*qY );
}

void FTDistribution2DCauchy::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("omega_x", &m_omega_x);
    getParameterPool()->registerParameter("omega_y", &m_omega_y);
}
