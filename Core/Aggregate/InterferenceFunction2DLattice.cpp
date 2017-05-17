// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction2DLattice.cpp
//! @brief     Implements class InterferenceFunction2DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunction2DLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "Macros.h"
#include "MathConstants.h"
#include "RealParameter.h"


InterferenceFunction2DLattice::InterferenceFunction2DLattice(const Lattice2D& lattice)
{
    setName(BornAgain::InterferenceFunction2DLatticeType);
    setLattice(lattice);
}

//! Constructor of two-dimensional interference function.
//! @param length_1: length of first lattice vector
//! @param length_2: length of second lattice vector
//! @param alpha: angle between lattice vectors in radians
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DLattice::InterferenceFunction2DLattice(double length_1, double length_2,
                                                             double alpha, double xi)
    : m_na(0), m_nb(0)
{
    setName(BornAgain::InterferenceFunction2DLatticeType);
    setLattice(BasicLattice(length_1, length_2, alpha, xi));
}

InterferenceFunction2DLattice::~InterferenceFunction2DLattice()
{
}

InterferenceFunction2DLattice* InterferenceFunction2DLattice::clone() const
{
    return new InterferenceFunction2DLattice(*this);
}

//! Creates square lattice.
//! @param lattice_length: length of first and second lattice vectors
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DLattice* InterferenceFunction2DLattice::createSquare(
double lattice_length, double xi)
{
    return new InterferenceFunction2DLattice(SquareLattice(lattice_length, xi));
}

//! Creates hexagonal lattice.
//! @param lattice_length: length of first and second lattice vectors
//! @param xi: rotation of lattice with respect to x-axis in radians
InterferenceFunction2DLattice* InterferenceFunction2DLattice::createHexagonal(
    double lattice_length, double xi)
{
    return new InterferenceFunction2DLattice(HexagonalLattice(lattice_length, xi));
}

//! Sets two-dimensional decay function.
//! @param decay: two-dimensional decay function in reciprocal space
void InterferenceFunction2DLattice::setDecayFunction(const IFTDecayFunction2D& decay)
{
    m_decay.reset(decay.clone());
    registerChild(m_decay.get());
    initialize_calc_factors();
}

double InterferenceFunction2DLattice::evaluate(const kvector_t q) const
{
    if (!m_decay)
        throw Exceptions::NullPointerException("InterferenceFunction2DLattice::evaluate"
                                   " -> Error! No decay function defined.");
    double result = 0.0;
    double qxr = q.x();
    double qyr = q.y();
    double qx_frac, qy_frac;
    calculateReciprocalVectorFraction(qxr, qyr, qx_frac, qy_frac);

    for (int i = -m_na - 1; i < m_na + 2; ++i) {
        for (int j = -m_nb - 1; j < m_nb + 2; ++j) {
            double qx = qx_frac + i * m_sbase.m_asx + j * m_sbase.m_bsx;
            double qy = qy_frac + i * m_sbase.m_asy + j * m_sbase.m_bsy;
            result += interferenceAtOneRecLatticePoint(qx, qy);
        }
    }
    return getParticleDensity()*result;
}

const Lattice2D& InterferenceFunction2DLattice::lattice() const
{
    if(!m_lattice)
        throw std::runtime_error("InterferenceFunction2DLattice::lattice() -> Error. "
                                 "No lattice defined.");
    return *m_lattice;
}

double InterferenceFunction2DLattice::getParticleDensity() const
{
    double area = m_lattice->unitCellArea();
    return area == 0.0 ? 0.0 : 1.0/area;
}

std::vector<const INode*> InterferenceFunction2DLattice::getChildren() const
{
    return std::vector<const INode*>() << m_decay << m_lattice;
}

void InterferenceFunction2DLattice::onChange()
{
    initialize_rec_vectors();
    initialize_calc_factors();
}

InterferenceFunction2DLattice::InterferenceFunction2DLattice(
        const InterferenceFunction2DLattice& other)
{
    setName(other.getName());

    if(other.m_lattice)
        setLattice(*other.m_lattice);

    if(other.m_decay)
        setDecayFunction(*other.m_decay);
}

void InterferenceFunction2DLattice::setLattice(const Lattice2D& lattice)
{
    m_lattice.reset(lattice.clone());
    registerChild(m_lattice.get());
    initialize_rec_vectors();
}

double InterferenceFunction2DLattice::interferenceAtOneRecLatticePoint(double qx, double qy) const
{
    if (!m_decay)
        throw Exceptions::NullPointerException(
            "InterferenceFunction2DLattice::interferenceAtOneRecLatticePoint"
            " -> Error! No decay function defined.");
    double qp1, qp2;
    double gamma = m_lattice->rotationAngle() + m_decay->getGamma();
    double delta = m_decay->getDelta();
    transformToPrincipalAxes(qx, qy, gamma, delta, qp1, qp2);
    return m_decay->evaluate(qp1, qp2);
}

void InterferenceFunction2DLattice::transformToPrincipalAxes(
    double qx, double qy, double gamma, double delta, double &q_pa_1, double &q_pa_2) const
{
    q_pa_1 = qx * std::cos(gamma) + qy * std::sin(gamma);
    q_pa_2 = qx * std::cos(gamma + delta) + qy * std::sin(gamma + delta);
}

void InterferenceFunction2DLattice::calculateReciprocalVectorFraction(
    double qx, double qy, double &qx_frac, double &qy_frac) const
{
    double a = m_lattice->length1();
    double b = m_lattice->length2();
    double xi = m_lattice->rotationAngle();
    double xialpha = xi + m_lattice->latticeAngle();

    int qa_int = std::lround(a * (qx * std::cos(xi) + qy * std::sin(xi)) / M_TWOPI);
    int qb_int = std::lround(b * (qx * std::cos(xialpha) + qy * std::sin(xialpha)) / M_TWOPI);
    qx_frac = qx - qa_int * m_sbase.m_asx - qb_int * m_sbase.m_bsx;
    qy_frac = qy - qa_int * m_sbase.m_asy - qb_int * m_sbase.m_bsy;
}

void InterferenceFunction2DLattice::initialize_rec_vectors()
{
    if(!m_lattice)
        throw std::runtime_error("InterferenceFunction2DLattice::initialize_rec_vectors() -> "
                                 "Error. No lattice defined yet");

    m_sbase = m_lattice->reciprocalBases();
}

void InterferenceFunction2DLattice::initialize_calc_factors()
{
    if (!m_decay)
        throw Exceptions::NullPointerException(
            "InterferenceFunction2DLattice::initialize_calc_factors"
            " -> Error! No probability distribution function defined.");

    double coherence_length_x = m_decay->getDecayLengthX();
    double coherence_length_y = m_decay->getDecayLengthY();

    // number of reciprocal lattice points to use
    double qa_max(0.0), qb_max(0.0);

    m_decay->transformToStarBasis(nmax / coherence_length_x, nmax / coherence_length_y,
                                 m_lattice->latticeAngle(), m_lattice->length1(),
                                 m_lattice->length2(), qa_max, qb_max);
    m_na = std::lround(std::abs(qa_max));
    m_nb = std::lround(std::abs(qb_max));
}
