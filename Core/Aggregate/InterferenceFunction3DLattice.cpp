// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunction3DLattice.cpp
//! @brief     Implements class InterferenceFunction3DLattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/InterferenceFunction3DLattice.h"
#include "Core/Aggregate/IPeakShape.h"
#include "Core/Basics/Exceptions.h"
#include <algorithm>

InterferenceFunction3DLattice::InterferenceFunction3DLattice(const Lattice& lattice)
    : m_lattice(lattice), mP_peak_shape(nullptr), m_rec_radius(0.0)
{
    setName("Interference3DLattice");
    initRecRadius();
}

InterferenceFunction3DLattice::~InterferenceFunction3DLattice() = default;

InterferenceFunction3DLattice* InterferenceFunction3DLattice::clone() const
{
    return new InterferenceFunction3DLattice(*this);
}

void InterferenceFunction3DLattice::setPeakShape(const IPeakShape& peak_shape)
{
    mP_peak_shape.reset(peak_shape.clone());
}

const Lattice& InterferenceFunction3DLattice::lattice() const
{
    return m_lattice;
}

std::vector<const INode*> InterferenceFunction3DLattice::getChildren() const
{
    return {};
}

void InterferenceFunction3DLattice::onChange()
{
    initRecRadius();
}

double InterferenceFunction3DLattice::iff_without_dw(const kvector_t q) const
{
    if (!mP_peak_shape)
        throw std::runtime_error("InterferenceFunction3DLattice::evaluate: "
                                 "no peak shape defined");
    kvector_t center = q;
    double radius = 2.1 * m_rec_radius;
    double inner_radius = 0.0;
    if (mP_peak_shape->angularDisorder()) {
        center = kvector_t(0.0, 0.0, 0.0);
        inner_radius = std::max(0.0, q.mag() - radius);
        radius += q.mag();
    }
    auto rec_vectors = m_lattice.reciprocalLatticeVectorsWithinRadius(center, radius);
    double result = 0.0;
    for (const auto& q_rec : rec_vectors) {
        if (!(q_rec.mag() < inner_radius)) {
            result += mP_peak_shape->evaluate(q, q_rec);
        }
    }
    return result;
}

InterferenceFunction3DLattice::InterferenceFunction3DLattice(
    const InterferenceFunction3DLattice& other)
    : IInterferenceFunction(other), m_lattice(other.m_lattice), mP_peak_shape(nullptr),
      m_rec_radius(0.0)
{
    setName(other.getName());
    initRecRadius();
    if (other.mP_peak_shape)
        setPeakShape(*other.mP_peak_shape);
}

void InterferenceFunction3DLattice::initRecRadius()
{
    kvector_t a1 = m_lattice.getBasisVectorA();
    kvector_t a2 = m_lattice.getBasisVectorB();
    kvector_t a3 = m_lattice.getBasisVectorC();

    m_rec_radius = std::max(M_PI / a1.mag(), M_PI / a2.mag());
    m_rec_radius = std::max(m_rec_radius, M_PI / a3.mag());
}
