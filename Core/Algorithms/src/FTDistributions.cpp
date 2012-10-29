#include "FTDistributions.h"
#include <cmath>

FTDistribution2DCauchy::FTDistribution2DCauchy(double omega_x, double omega_y)
: IFTDistribution2D(omega_x, omega_y)
{
}

FTDistribution2DCauchy* FTDistribution2DCauchy::clone() const
{
    return new FTDistribution2DCauchy(m_omega_x, m_omega_y);
}

double FTDistribution2DCauchy::evaluate(double qx, double qy) const
{
    double sum_sq = qx*qx*m_omega_x*m_omega_x + qy*qy*m_omega_y*m_omega_y;
    return std::pow(1.0 + sum_sq, -1.5);
}
