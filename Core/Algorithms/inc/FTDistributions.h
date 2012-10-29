#ifndef FTDISTRIBUTIONS_H_
#define FTDISTRIBUTIONS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FTDistributions.h
//! @brief  Definition of Fourier Transformed distributions
//! @author Scientific Computing Group at FRM II
//! @date   Oct 26, 2012

class IFTDistribution1D
{
public:
    IFTDistribution1D(double omega) : m_omega(omega) {}
    virtual ~IFTDistribution1D() {}

    virtual double evaluate(double q) const=0;
protected:
    double m_omega;
};

class IFTDistribution2D
{
public:
    IFTDistribution2D(double omega_x, double omega_y) : m_omega_x(omega_x), m_omega_y(omega_y) {}
    virtual ~IFTDistribution2D() {}

    virtual IFTDistribution2D *clone() const=0;

    virtual double evaluate(double qx, double qy) const=0;
protected:
    double m_omega_x;
    double m_omega_y;
};

class FTDistribution2DCauchy : public IFTDistribution2D
{
public:
    FTDistribution2DCauchy(double omega_x, double omega_y);
    virtual ~FTDistribution2DCauchy() {}

    virtual FTDistribution2DCauchy *clone() const;

    virtual double evaluate(double qx, double qy) const;
};

#endif /* FTDISTRIBUTIONS_H_ */
