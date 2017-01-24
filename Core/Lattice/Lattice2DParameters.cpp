// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice2DParameters.cpp
//! @brief     Implements class Lattice2DParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Lattice2DParameters.h"
#include "BornAgainNamespace.h"
#include "RealParameter.h"
#include "MathConstants.h"

double Lattice2DParameters::getUnitCellArea() const
{
    return std::abs(m_length_1*m_length_2*std::sin(m_angle));
}

Lattice2D::Lattice2D(double length1, double length2, double angle, double rotation_angle)
    : m_length1(length1)
    , m_length2(length2)
    , m_angle(angle)
    , m_xi(rotation_angle)
{
    if(m_length1 <= 0.0 || m_length2 <= 0.0)
        throw std::runtime_error("Lattice2D::Lattice2D() -> Error. Lattice length can't be "
                                 "negative or zero.");
}

double Lattice2D::unitCellArea() const
{
    return std::abs(m_length1*m_length2*std::sin(m_angle));
}

Lattice2D::ReciprocalBases Lattice2D::reciprocalBases() const
{
    double sinalpha = std::sin(latticeAngle());
    double ainv = M_TWOPI / length1() / sinalpha;
    double binv = M_TWOPI / length2() / sinalpha;
    double xi = rotationAngle();
    double xialpha = xi + latticeAngle();

    return {+ainv * std::sin(xialpha),
            -ainv * std::cos(xialpha),
            -binv * std::sin(xi),
            +binv * std::cos(xi)};
}

void Lattice2D::onChange()
{
    if(parent())
        parent()->onChange();
}

Lattice2D::Lattice2D(const Lattice2D& other)
{
    m_length1 = other.m_length1;
    m_length2 = other.m_length2;
    m_angle = other.m_angle;
    m_xi = other.m_xi;
    setName(other.getName());
}

// --------------------------------------------------------------------------------------------- //

BasicLattice::BasicLattice(double length1, double length2, double angle, double rotation_angle)
    : Lattice2D(length1, length2, angle, rotation_angle)
{
    setName(BornAgain::BasicLatticeType);
    init_parameters();
}

BasicLattice* BasicLattice::clone() const
{
    return new BasicLattice(*this);
}

BasicLattice::BasicLattice(const BasicLattice& other)
    : Lattice2D(other)
{
    init_parameters();
}

void BasicLattice::init_parameters()
{
    registerParameter(BornAgain::LatticeLength1, &m_length1).setUnit("nm").setPositive();
    registerParameter(BornAgain::LatticeLength2, &m_length2).setUnit("nm").setPositive();
    registerParameter(BornAgain::LatticeAngle, &m_angle).setUnit("rad");
    registerParameter(BornAgain::Xi,    &m_xi   ).setUnit("rad");
}

// --------------------------------------------------------------------------------------------- //

SquareLattice::SquareLattice(double length, double rotation_angle)
    : Lattice2D(length, length, M_PI/2.0, rotation_angle)
{
    setName(BornAgain::SquareLatticeType);
    init_parameters();
}

SquareLattice* SquareLattice::clone() const
{
    return new SquareLattice(*this);
}

SquareLattice::SquareLattice(const SquareLattice& other)
    : Lattice2D(other)
{
    init_parameters();
}

void SquareLattice::init_parameters()
{
    registerParameter(BornAgain::LatticeLength, &m_length1).setUnit("nm").setPositive();
    registerParameter(BornAgain::Xi, &m_xi).setUnit("rad");
}

// --------------------------------------------------------------------------------------------- //

HexagonalLattice::HexagonalLattice(double length, double rotation_angle)
    : Lattice2D(length, length, M_TWOPI / 3.0, rotation_angle)
{
    setName(BornAgain::HexagonalLatticeType);
    init_parameters();
}

HexagonalLattice* HexagonalLattice::clone() const
{
    return new HexagonalLattice(*this);
}

HexagonalLattice::HexagonalLattice(const HexagonalLattice& other)
    : Lattice2D(other)
{
    init_parameters();
}

void HexagonalLattice::init_parameters()
{
    registerParameter(BornAgain::LatticeLength, &m_length1).setUnit("nm").setPositive();
    registerParameter(BornAgain::Xi, &m_xi).setUnit("rad");
}
