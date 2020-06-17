// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DSuperLattice.cpp
//! @brief     Implements class InterferenceFunction2DSuperLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunction2DSuperLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "InterferenceFunctionNone.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealParameter.h"

#include <limits>

using MathFunctions::Laue;

InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(const Lattice2D& lattice,
                                                                       unsigned size_1,
                                                                       unsigned size_2)
    : m_integrate_xi(false), mP_substructure(nullptr), m_size_1(size_1), m_size_2(size_2)
{
    setName(BornAgain::InterferenceFunction2DSuperLattice);
    setLattice(lattice);
    setSubstructureIFF(InterferenceFunctionNone());
    init_parameters();
}

//! Constructor of two-dimensional interference function.
//! @param length_1: length of first lattice vector in nanometers
//! @param length_2: length of second lattice vector  in nanometers
//! @param alpha: angle between lattice vectors in radians
//! @param xi: rotation of lattice with respect to x-axis (beam direction) in radians
InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(
    double length_1, double length_2, double alpha, double xi, unsigned size_1, unsigned size_2)
    : m_integrate_xi(false), mP_substructure(nullptr), m_size_1(size_1), m_size_2(size_2)
{
    setName(BornAgain::InterferenceFunction2DSuperLattice);
    setLattice(BasicLattice(length_1, length_2, alpha, xi));
    setSubstructureIFF(InterferenceFunctionNone());
    init_parameters();
}

InterferenceFunction2DSuperLattice::~InterferenceFunction2DSuperLattice() = default;

InterferenceFunction2DSuperLattice* InterferenceFunction2DSuperLattice::clone() const
{
    return new InterferenceFunction2DSuperLattice(*this);
}

void InterferenceFunction2DSuperLattice::setSubstructureIFF(const IInterferenceFunction& sub_iff)
{
    mP_substructure.reset(sub_iff.clone());
    registerChild(mP_substructure.get());
}

const IInterferenceFunction& InterferenceFunction2DSuperLattice::substructureIFF() const
{
    return *mP_substructure;
}

//! Creates square lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DSuperLattice*
InterferenceFunction2DSuperLattice::createSquare(double lattice_length, double xi, unsigned size_1,
                                                 unsigned size_2)
{
    return new InterferenceFunction2DSuperLattice(SquareLattice(lattice_length, xi), size_1,
                                                  size_2);
}

//! Creates hexagonal lattice.
//! @param lattice_length: length of first and second lattice vectors in nanometers
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DSuperLattice*
InterferenceFunction2DSuperLattice::createHexagonal(double lattice_length, double xi,
                                                    unsigned size_1, unsigned size_2)
{
    return new InterferenceFunction2DSuperLattice(HexagonalLattice(lattice_length, xi), size_1,
                                                  size_2);
}

double InterferenceFunction2DSuperLattice::evaluate(const kvector_t q, double outer_iff) const
{
    m_outer_iff = outer_iff;
    m_qx = q.x();
    m_qy = q.y();
    if (!m_integrate_xi)
        return interferenceForXi(mP_lattice->rotationAngle());
    return m_integrator.integrate([&](double xi) -> double { return interferenceForXi(xi); }, 0.0,
                                  M_TWOPI)
           / M_TWOPI;
}

void InterferenceFunction2DSuperLattice::setIntegrationOverXi(bool integrate_xi)
{
    m_integrate_xi = integrate_xi;
    mP_lattice->setRotationEnabled(!m_integrate_xi); // deregister Xi in the case of integration
}

const Lattice2D& InterferenceFunction2DSuperLattice::lattice() const
{
    if (!mP_lattice)
        throw std::runtime_error("InterferenceFunctionFinite2DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *mP_lattice;
}

std::vector<const INode*> InterferenceFunction2DSuperLattice::getChildren() const
{
    return std::vector<const INode*>() << mP_lattice << mP_substructure;
}

double InterferenceFunction2DSuperLattice::iff_without_dw(const kvector_t q) const
{
    double a = mP_lattice->length1();
    double b = mP_lattice->length2();
    double xialpha = m_xi + mP_lattice->latticeAngle();

    double qadiv2 = (q.x() * a * std::cos(m_xi) + q.y() * a * std::sin(m_xi)) / 2.0;
    double qbdiv2 = (q.x() * b * std::cos(xialpha) + q.y() * b * std::sin(xialpha)) / 2.0;
    double ampl = Laue(qadiv2, m_size_1) * Laue(qbdiv2, m_size_2);
    return ampl * ampl / (m_size_1 * m_size_2);
}

InterferenceFunction2DSuperLattice::InterferenceFunction2DSuperLattice(
    const InterferenceFunction2DSuperLattice& other)
    : IInterferenceFunction(other), m_size_1(other.m_size_1), m_size_2(other.m_size_2)
{
    setName(other.getName());
    if (other.mP_lattice)
        setLattice(*other.mP_lattice);
    setSubstructureIFF(*other.mP_substructure);
    setIntegrationOverXi(other.integrationOverXi());
    init_parameters();
}

void InterferenceFunction2DSuperLattice::setLattice(const Lattice2D& lattice)
{
    mP_lattice.reset(lattice.clone());
    registerChild(mP_lattice.get());
}

void InterferenceFunction2DSuperLattice::init_parameters() {}

double InterferenceFunction2DSuperLattice::interferenceForXi(double xi) const
{
    m_xi = xi;
    kvector_t q = kvector_t(m_qx, m_qy, 0.0);
    double outer_iff = iff_no_inner(q, m_outer_iff);

    double delta_xi = xi - mP_lattice->rotationAngle();
    q = q.rotatedZ(-delta_xi);
    return mP_substructure->evaluate(q, outer_iff);
}
