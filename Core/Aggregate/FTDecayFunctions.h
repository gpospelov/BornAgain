// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDecayFunctions.h
//! @brief     Defines classes IFTDecayFunction1D, IFTDecayFunction2D,
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FTDECAYFUNCTIONS_H
#define FTDECAYFUNCTIONS_H

#include "IParameterized.h"
#include "Pi.h"


//! Interface for one-dimensional decay function in reciprocal space.
//! @ingroup algorithms_internal
class BA_CORE_API_ IFTDecayFunction1D : public IParameterized
{
public:
    IFTDecayFunction1D(double omega) : m_omega(omega) {}
    virtual ~IFTDecayFunction1D() {}

    virtual IFTDecayFunction1D* clone() const=0;
    virtual double evaluate(double q) const=0;
    void setOmega(double omega) { m_omega = omega; }
    double getOmega() const { return m_omega; }

    friend std::ostream& operator<<(std::ostream& ostr, const IFTDecayFunction1D& m) {
        m.print(ostr); return ostr; }

protected:
    virtual void print(std::ostream& ostr) const;
    virtual void init_parameters();
    double m_omega;
};


//! One-dimensional Cauchy decay function in reciprocal space;
//! corresponds to exp(-|x|/omega) in real space.
//! @ingroup algorithms
class BA_CORE_API_ FTDecayFunction1DCauchy : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DCauchy(double omega);
    virtual ~FTDecayFunction1DCauchy() {}

    virtual FTDecayFunction1DCauchy* clone() const {
        return new FTDecayFunction1DCauchy(m_omega); }

    virtual double evaluate(double q) const;
};


//! One-dimensional Gauss decay function in reciprocal space;
//! corresponds to exp[-x^2/(2*omega^2)] in real space.
//! @ingroup algorithms
class BA_CORE_API_ FTDecayFunction1DGauss : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DGauss(double omega);
    virtual ~FTDecayFunction1DGauss() {}

    virtual FTDecayFunction1DGauss* clone() const {
        return new FTDecayFunction1DGauss(m_omega); }

    virtual double evaluate(double q) const;
};


//! One-dimensional triangle decay function in reciprocal space;
//! corresponds to 1-|x|/omega if |x|<omega (and 0 otherwise) in real space.
//! @ingroup algorithms
class BA_CORE_API_ FTDecayFunction1DTriangle : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DTriangle(double omega);
    virtual ~FTDecayFunction1DTriangle() {}

    virtual FTDecayFunction1DTriangle* clone() const {
        return new FTDecayFunction1DTriangle(m_omega); }

    virtual double evaluate(double q) const;
};


//! One-dimensional pseudo-Voigt decay function in reciprocal space;
//! corresponds to eta*Gauss + (1-eta)*Cauchy.
//! @ingroup algorithms
class BA_CORE_API_ FTDecayFunction1DVoigt : public IFTDecayFunction1D
{
public:
    FTDecayFunction1DVoigt(double omega, double eta);
    virtual ~FTDecayFunction1DVoigt() {}

    virtual FTDecayFunction1DVoigt* clone() const {
        return new FTDecayFunction1DVoigt(m_omega, m_eta); }

    virtual double evaluate(double q) const;

    virtual double getEta() const { return m_eta;}

protected:
    virtual void init_parameters();
    double m_eta;
};


//! Interface for two-dimensional decay function in reciprocal space.
//! @ingroup algorithms_internal
class BA_CORE_API_ IFTDecayFunction2D : public IParameterized
{
public:
    IFTDecayFunction2D(double decay_length_x, double decay_length_y,
                       double gamma=0, double delta=Pi::PID2);
    virtual ~IFTDecayFunction2D() {}

    virtual IFTDecayFunction2D* clone() const=0;

    //! set angle between first lattice vector and X-axis of distribution (both in direct space)
    void setGamma(double gamma) { m_gamma = gamma; }

    //! get angle between first lattice vector and X-axis of distribution (both in direct space)
    double getGamma() const { return m_gamma; }

    //! get angle between X- and Y-axis of distribution (in direct space)
    double getDelta() const { return m_delta; }

    //! get coherence length in X-direction
    double getDecayLengthX() const { return m_omega_x; }

    //! get coherence length in Y-direction
    double getDecayLengthY() const { return m_omega_y; }

    //! evaluate Fourier transformed decay function for q in X,Y coordinates
    virtual double evaluate(double qx, double qy) const=0;

    //! transform back to a*, b* basis:
    void transformToStarBasis(double qX, double qY,
            double alpha, double a, double b, double& qa, double& qb) const;

    friend std::ostream& operator<<(std::ostream& ostr, const IFTDecayFunction2D& m)
    { m.print(ostr); return ostr; }

protected:
    virtual void print(std::ostream& ostr) const;
    virtual void init_parameters();
    double m_omega_x;
    double m_omega_y;
    double m_gamma;
    double m_delta;
};


//! Two-dimensional Cauchy decay function in reciprocal space;
//! corresponds to exp(-r) in real space,
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup algorithms
class BA_CORE_API_ FTDecayFunction2DCauchy : public IFTDecayFunction2D
{
public:
    FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y,
                            double gamma=0, double delta=Pi::PID2);

    virtual ~FTDecayFunction2DCauchy() {}

    virtual FTDecayFunction2DCauchy* clone() const {
        return new FTDecayFunction2DCauchy(m_omega_x, m_omega_y, m_gamma, m_delta); }

    virtual double evaluate(double qx, double qy) const;
};


//! Two-dimensional Gauss decay function in reciprocal space;
//! corresponds to exp(-r^2/2) in real space,
//! with \f$r=\sqrt{(\frac{x}{\omega_x})^2 + (\frac{y}{\omega_y})^2}\f$.
//! @ingroup algorithms
class BA_CORE_API_ FTDecayFunction2DGauss : public IFTDecayFunction2D
{
public:
    FTDecayFunction2DGauss(double decay_length_x, double decay_length_y,
                           double gamma=0, double delta=Pi::PID2);

    virtual ~FTDecayFunction2DGauss() {}

    virtual FTDecayFunction2DGauss* clone() const {
        return new FTDecayFunction2DGauss(m_omega_x, m_omega_y, m_gamma, m_delta); }


    virtual double evaluate(double qx, double qy) const;
};

//! Two-dimensional pseudo-Voigt decay function in reciprocal space;
//! corresponds to eta*Gauss + (1-eta)*Cauchy.
//! @ingroup algorithms
class BA_CORE_API_ FTDecayFunction2DVoigt : public IFTDecayFunction2D
{
public:
    FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y, double eta,
                           double gamma=0, double delta=Pi::PID2);

    virtual ~FTDecayFunction2DVoigt() {}

    virtual FTDecayFunction2DVoigt* clone() const {
        return new FTDecayFunction2DVoigt(m_omega_x, m_omega_y, m_eta, m_gamma, m_delta); }

    virtual double evaluate(double qx, double qy) const;

    virtual double getEta() const { return m_eta; }

protected:
    virtual void init_parameters();
    double m_eta;
};

#endif // FTDECAYFUNCTIONS_H
