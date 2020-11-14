// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/LatticeUtils.cpp
//! @brief     Implements factory functions for different types of lattices and orientations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Sample/Lattice/LatticeUtils.h"
#include "Sample/Lattice/BakeLattice.h"
#include "Sample/Lattice/ILatticeOrientation.h"

Lattice LatticeUtils::createOrientedFCCLattice(double lattice_constant,
                                               const ILatticeOrientation& orientation)
{
    const Lattice prim_cubic = bake::createCubicLattice(1.0);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_cubic);
    const Transform3D trafo = P_orientation->transformation();
    const Lattice fcc = bake::createFCCLattice(lattice_constant);
    return fcc.transformed(trafo);
}

Lattice LatticeUtils::createOrientedHCPLattice(double a, double c,
                                               const ILatticeOrientation& orientation)
{
    const Lattice prim_hexagonal = bake::createHexagonalLattice(1.0, c / a);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_hexagonal);
    const Transform3D trafo = P_orientation->transformation();
    const Lattice hcp = bake::createHCPLattice(a, c);
    return hcp.transformed(trafo);
}

Lattice LatticeUtils::createOrientedBCTLattice(double a, double c,
                                               const ILatticeOrientation& orientation)
{
    const Lattice prim_tetragonal = bake::createTetragonalLattice(1.0, c / a);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_tetragonal);
    const Transform3D trafo = P_orientation->transformation();
    const Lattice hcp = bake::createBCTLattice(a, c);
    return hcp.transformed(trafo);
}
