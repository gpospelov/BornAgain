// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions2D.h
//! @brief     Declares interface class IFTDistribution2D, and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FTDISTRIBUTIONS2D_H
#define FTDISTRIBUTIONS2D_H

#include "IParameterized.h" // inheriting from
#include "Units.h"

// ************************************************************************** //
//! @class IFTDistribution2D
// ************************************************************************** //
//! @ingroup algorithms_internal
//! @brief Interface for 2 dimensional distributions in Fourier space.

class BA_CORE_API_ IFTDistribution2D : public IParameterized
{
public:
    IFTDistribution2D(double coherence_length_x, double coherence_length_y,
                      double gamma=0, double delta=Units::PID2);
    virtual ~IFTDistribution2D() {}

    virtual IFTDistribution2D* clone() const=0;

    void setGamma(double gamma) { m_gamma = gamma; }
    double getGamma() const { return m_gamma; }

    double getDelta() const { return m_delta; }

    double getCoherenceLengthX() const { return m_coherence_length_x; }
    double getCoherenceLengthY() const { return m_coherence_length_y; }

    //! evaluate Fourier transformed distribution for q in X,Y coordinates
    //! the original distribution (in real space) is assumed to be normalized:
    //! total integral is equal to 1
    virtual double evaluate(double qx, double qy) const=0;

    friend std::ostream& operator<<(std::ostream& ostr, const IFTDistribution2D& m) {
        m.print(ostr); return ostr; }

protected:
    double sumsq( double qx, double qy) const {
        return qx*qx*m_coherence_length_x*m_coherence_length_x +
            qy*qy*m_coherence_length_y*m_coherence_length_y; }

    virtual void print(std::ostream& ostr) const;
    void init_parameters();

    double m_coherence_length_x; //!< Coherence length in X-direction.
    double m_coherence_length_y; //!< Coherence length in Y-direction.
    //! Angle in direct space between first lattice vector and X-axis of distribution.
    double m_gamma;
    //! Angle in direct space between X- and Y-axis of distribution.
    double m_delta;
};

// ************************************************************************** //
//! @class FTDistribution2DCauchy
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 2 dimensional Cauchy distribution in Fourier space.
//! Corresponds to a normalized exp(-r) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$

class BA_CORE_API_ FTDistribution2DCauchy : public IFTDistribution2D
{
public:
    FTDistribution2DCauchy(double coherence_length_x, double coherence_length_y,
                           double gamma=0, double delta=Units::PID2);

    virtual ~FTDistribution2DCauchy() {}

    FTDistribution2DCauchy* clone() const final {
        return new FTDistribution2DCauchy(
            m_coherence_length_x, m_coherence_length_y, m_gamma, m_delta); }

    virtual double evaluate(double qx, double qy) const;
};

// ************************************************************************** //
//! @class FTDistribution2DGauss
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 2 dimensional Gauss distribution in Fourier space.
//! Corresponds to normalized exp(-r^2/2) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$

class BA_CORE_API_ FTDistribution2DGauss : public IFTDistribution2D
{
public:
    FTDistribution2DGauss(double coherence_length_x, double coherence_length_y,
                          double gamma=0, double delta=Units::PID2);

    virtual ~FTDistribution2DGauss() {}

    FTDistribution2DGauss* clone() const final {
        return new FTDistribution2DGauss(
            m_coherence_length_x, m_coherence_length_y, m_gamma, m_delta); }

    virtual double evaluate(double qx, double qy) const;
};

// ************************************************************************** //
//! @class FTDistribution2DGate
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 2 dimensional gate distribution in Fourier space
//! Corresponds to normalized constant if r<1 (and 0 otherwise) in real space.
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$

class BA_CORE_API_ FTDistribution2DGate : public IFTDistribution2D
{
public:
    FTDistribution2DGate(double coherence_length_x, double coherence_length_y,
                         double gamma=0, double delta=Units::PID2);

    virtual ~FTDistribution2DGate() {}

    FTDistribution2DGate* clone() const final {
        return new FTDistribution2DGate(
            m_coherence_length_x, m_coherence_length_y, m_gamma, m_delta); }

    virtual double evaluate(double qx, double qy) const;
};

// ************************************************************************** //
//! @class FTDistribution2DCone
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 2 dimensional cone distribution in Fourier space.
//! Corresponds to 1-r if r<1 (and 0 otherwise) in real space
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$

class BA_CORE_API_ FTDistribution2DCone : public IFTDistribution2D
{
public:
    FTDistribution2DCone(double coherence_length_x, double coherence_length_y,
                         double gamma=0, double delta=Units::PID2);

    virtual ~FTDistribution2DCone() {}

    FTDistribution2DCone* clone() const final {
        return new FTDistribution2DCone(
            m_coherence_length_x, m_coherence_length_y, m_gamma, m_delta); }

    virtual double evaluate(double qx, double qy) const;

private:
    //! second part of the integrand:
    //! \f$u^2\cdot J_0(u)\f$
    double coneIntegrand2(double value) const;
};

// ************************************************************************** //
//! @class FTDistribution2DVoigt
// ************************************************************************** //
//! @ingroup algorithms
//! @brief 2 dimensional Voigt distribution in Fourier space.
//! Corresponds to eta*Gauss + (1-eta)*Cauchy

class BA_CORE_API_ FTDistribution2DVoigt : public IFTDistribution2D
{
public:
    FTDistribution2DVoigt(double coherence_length_x, double coherence_length_y,
                          double eta, double gamma=0, double delta=Units::PID2);
    virtual ~FTDistribution2DVoigt() {}

    FTDistribution2DVoigt* clone() const final {
        return new FTDistribution2DVoigt(
            m_coherence_length_x, m_coherence_length_y, m_eta, m_gamma, m_delta); }

    virtual double evaluate(double qx, double qy) const;

    virtual double getEta() const { return m_eta;}

protected:
    double m_eta;
};

#endif // FTDISTRIBUTIONS2D_H
