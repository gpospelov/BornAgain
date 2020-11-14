// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/Lattice.cpp
//! @brief     Implements class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Sample/Lattice/Lattice.h"
#include "Base/Const/MathConstants.h"
#include "Base/Vector/Transform3D.h"
#include "Param/Base/RealParameter.h"
#include "Sample/Lattice/ISelectionRule.h"
#include <gsl/gsl_linalg.h>

Lattice::Lattice()
    : m_a({1.0, 0.0, 0.0})
    , m_b({0.0, 1.0, 0.0})
    , m_c({0.0, 0.0, 1.0})
{
    setName("Lattice");
    initialize();
}

Lattice::Lattice(const kvector_t a, const kvector_t b, const kvector_t c)
    : m_a(a), m_b(b), m_c(c)
{
    setName("Lattice");
    initialize();
}

Lattice::Lattice(const Lattice& lattice)
    : INode()
    , m_a(lattice.m_a)
    , m_b(lattice.m_b)
    , m_c(lattice.m_c)
{
    setName("Lattice");
    initialize();
    if (lattice.m_selection_rule)
        setSelectionRule(*lattice.m_selection_rule);
}

Lattice::~Lattice() = default;

void Lattice::initialize()
{
    computeReciprocalVectors();
    if (!parameter(XComponentName("BasisA"))) {
        registerVector("BasisA", &m_a, "nm");
        registerVector("BasisB", &m_b, "nm");
        registerVector("BasisC", &m_c, "nm");
    }
}

void Lattice::onChange()
{
    computeReciprocalVectors();
}

Lattice Lattice::transformed(const Transform3D& transform) const
{
    kvector_t q1 = transform.transformed(m_a);
    kvector_t q2 = transform.transformed(m_b);
    kvector_t q3 = transform.transformed(m_c);
    Lattice result = {q1, q2, q3};
    if (m_selection_rule)
        result.setSelectionRule(*m_selection_rule);
    return result;
}

//! Currently unused but may be useful for checks
kvector_t Lattice::getMillerDirection(double h, double k, double l) const
{
    kvector_t direction = h * m_ra + k * m_rb + l * m_rc;
    return direction.unit();
}

double Lattice::volume() const
{
    return std::abs(m_a.dot(m_b.cross(m_c)));
}

//! Currently only used in tests
void Lattice::getReciprocalLatticeBasis(kvector_t& ra, kvector_t& rb, kvector_t& rc) const
{
    ra = m_ra;
    rb = m_rb;
    rc = m_rc;
}

ivector_t Lattice::getNearestReciprocalLatticeVectorCoordinates(const kvector_t q) const
{
    return {
        (int)std::lround(q.dot(m_a) / M_TWOPI),
        (int)std::lround(q.dot(m_b) / M_TWOPI),
        (int)std::lround(q.dot(m_c) / M_TWOPI)};
}

std::vector<kvector_t> Lattice::reciprocalLatticeVectorsWithinRadius(const kvector_t q,
                                                                     double dq) const
{
    ivector_t nearest_coords = getNearestReciprocalLatticeVectorCoordinates(q);

    int max_X = std::lround(m_a.mag() * dq / M_TWOPI);
    int max_Y = std::lround(m_b.mag() * dq / M_TWOPI);
    int max_Z = std::lround(m_c.mag() * dq / M_TWOPI);

    std::vector<kvector_t> ret;
    for (int index_X = -max_X; index_X <= max_X; ++index_X) {
        for (int index_Y = -max_Y; index_Y <= max_Y; ++index_Y) {
            for (int index_Z = -max_Z; index_Z <= max_Z; ++index_Z) {
                ivector_t coords(index_X + nearest_coords[0], index_Y + nearest_coords[1],
                                 index_Z + nearest_coords[2]);
                if (m_selection_rule && !m_selection_rule->coordinateSelected(coords))
                    continue;
                kvector_t latticePoint = coords[0] * m_ra + coords[1] * m_rb + coords[2] * m_rc;
                if ((latticePoint - q).mag() <= dq)
                    ret.push_back(latticePoint);
            }
        }
    }
    return ret;
}

void Lattice::computeReciprocalVectors() const
{
    kvector_t q23 = m_b.cross(m_c);
    kvector_t q31 = m_c.cross(m_a);
    kvector_t q12 = m_a.cross(m_b);
    m_ra = M_TWOPI / m_a.dot(q23) * q23;
    m_rb = M_TWOPI / m_b.dot(q31) * q31;
    m_rc = M_TWOPI / m_c.dot(q12) * q12;
}

void Lattice::setSelectionRule(const ISelectionRule& selection_rule)
{
    m_selection_rule.reset(selection_rule.clone());
}
