// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactor2DLattice.cpp
//! @brief     Implements class FormFactor2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactor2DLattice.h"
#include "BornAgainNamespace.h"
#include "WavevectorInfo.h"

namespace {
double SinNx_Div_Sinx(double x, unsigned N);
}

FormFactor2DLattice::FormFactor2DLattice(const IFormFactor& form_factor, const Lattice2D& lattice,
                                         unsigned size_1, unsigned size_2)
    : m_size_1(size_1)
    , m_size_2(size_2)
{
    setName(BornAgain::FF2DLattice);
    setFormFactor(form_factor);
    setLattice(lattice);
}

FormFactor2DLattice::FormFactor2DLattice(const IFormFactor& form_factor,
                                         double length_1, double length_2,
                                         double alpha, double xi, unsigned size_1, unsigned size_2)
    : m_size_1(size_1)
    , m_size_2(size_2)
{
    setName(BornAgain::FF2DLattice);
    setFormFactor(form_factor);
    setLattice(BasicLattice(length_1, length_2, alpha, xi));
}

FormFactor2DLattice*FormFactor2DLattice::clone() const
{
    return new FormFactor2DLattice(*mP_form_factor, *mP_lattice, m_size_1, m_size_2);
}

FormFactor2DLattice::~FormFactor2DLattice() =default;

complex_t FormFactor2DLattice::evaluate(const WavevectorInfo& wavevectors) const
{
    return getLatticeFactor(wavevectors)*mP_form_factor->evaluate(wavevectors);
}

Eigen::Matrix2cd FormFactor2DLattice::evaluatePol(const WavevectorInfo& wavevectors) const
{
    return getLatticeFactor(wavevectors)*mP_form_factor->evaluatePol(wavevectors);
}

void FormFactor2DLattice::setFormFactor(const IFormFactor& ff)
{
    mP_form_factor.reset(ff.clone());
}

void FormFactor2DLattice::setLattice(const Lattice2D& lattice)
{
    mP_lattice.reset(lattice.clone());
}

complex_t FormFactor2DLattice::getLatticeFactor(const WavevectorInfo& wavevectors) const
{
    static complex_t IM {0.0, 1.0};
    double a = mP_lattice->length1();
    double b = mP_lattice->length2();
    double xi = mP_lattice->rotationAngle();
    double xialpha = xi + mP_lattice->latticeAngle();
    kvector_t q = wavevectors.getQ().real();

    double qadiv2 = (q.x()*a*std::cos(xi) + q.y()*a*std::sin(xi)) / 2.0;
    double qbdiv2 = (q.x()*b*std::cos(xialpha) + q.y()*b*std::sin(xialpha)) / 2.0;
    double ampl = SinNx_Div_Sinx(qadiv2, m_size_1)*SinNx_Div_Sinx(qbdiv2, m_size_2);
    double s1 = static_cast<double>(m_size_1) - 1.0;
    double s2 = static_cast<double>(m_size_2) - 1.0;
    complex_t phase = std::exp(IM*s1*qadiv2)*std::exp(IM*s2*qbdiv2);
    return phase*ampl;
}

namespace {
double SinNx_Div_Sinx(double x, unsigned N) {
    static const double SQRT6DOUBLE_EPS = std::sqrt(6.0*std::numeric_limits<double>::epsilon());
    auto nd = static_cast<double>(N);
    if(std::abs(nd*x) < SQRT6DOUBLE_EPS)
        return nd;
    double num = std::sin(nd*x);
    double den = std::sin(x);
    return num/den;
}
}

