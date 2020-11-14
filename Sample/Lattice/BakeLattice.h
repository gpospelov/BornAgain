// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/BakeLattice.h
//! @brief     Defines class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_SAMPLE_LATTICE_BAKELATTICE_H
#define BORNAGAIN_SAMPLE_LATTICE_BAKELATTICE_H

class Lattice;

namespace bake
{

//! Returns a primitive cubic (cP) lattice with edge length a.
Lattice createCubicLattice(double a);

//! Returns a face-centered cubic (cF) lattice with edge length a.
Lattice createFCCLattice(double a);

//! Returns a primitive hexagonal (hP) lattice with hexagonal edge a and height c.
Lattice createHexagonalLattice(double a, double c);

//! TODO: Clarify how this is meant: HCP is not a Bravais lattice.
Lattice createHCPLattice(double a, double c);

//! Returns a primitive tetragonal (tP) lattice with square base edge a and height c.
Lattice createTetragonalLattice(double a, double c);

//! Returns a body-centered cubic (cI) lattice with edge length a.
//! TODO: Clarify meaning of c
Lattice createBCTLattice(double a, double c);

} // namespace bake

#endif // BORNAGAIN_SAMPLE_LATTICE_BAKELATTICE_H
