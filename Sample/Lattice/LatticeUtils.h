// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/LatticeUtils.h
//! @brief     Defines factory functions for different types of lattices and orientations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_SAMPLE_LATTICE_LATTICEUTILS_H
#define BORNAGAIN_SAMPLE_LATTICE_LATTICEUTILS_H

#include "Sample/Lattice/Lattice.h"

class ILatticeOrientation;

namespace LatticeUtils
{
Lattice createOrientedFCCLattice(double lattice_constant, const ILatticeOrientation& orientation);
Lattice createOrientedHCPLattice(double a, double c, const ILatticeOrientation& orientation);
Lattice createOrientedBCTLattice(double a, double c, const ILatticeOrientation& orientation);
} // namespace LatticeUtils

#endif // BORNAGAIN_SAMPLE_LATTICE_LATTICEUTILS_H
