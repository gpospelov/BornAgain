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

#include "InterferenceFunction3DLattice.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"


InterferenceFunction3DLattice::InterferenceFunction3DLattice(const Lattice& lattice)
    : m_lattice(lattice)
{}

InterferenceFunction3DLattice::~InterferenceFunction3DLattice() =default;


InterferenceFunction3DLattice* InterferenceFunction3DLattice::clone() const
{
    return new InterferenceFunction3DLattice(m_lattice);
}

double InterferenceFunction3DLattice::evaluate(const kvector_t q) const
{
    return 1.0;
}

const Lattice&InterferenceFunction3DLattice::lattice() const
{
    return m_lattice;
}

double InterferenceFunction3DLattice::getParticleDensity() const
{
    return 0.0;
}

std::vector<const INode*> InterferenceFunction3DLattice::getChildren() const
{
    return {};
}

void InterferenceFunction3DLattice::onChange()
{}
