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
#include "Sample/Lattice/ILatticeOrientation.h"

Lattice LatticeUtils::createFCCLattice(double lattice_constant,
                                       const ILatticeOrientation& orientation)
{
    const Lattice prim_cubic = Lattice::createCubicLattice(1.0);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_cubic);
    const Transform3D trafo = P_orientation->transformation();
    const Lattice fcc = Lattice::createFCCLattice(lattice_constant);
    return fcc.transformed(trafo);
}

Lattice LatticeUtils::createHCPLattice(double a, double c, const ILatticeOrientation& orientation)
{
    const Lattice prim_hexagonal = Lattice::createHexagonalLattice(1.0, c / a);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_hexagonal);
    const Transform3D trafo = P_orientation->transformation();
    const Lattice hcp = Lattice::createHCPLattice(a, c);
    return hcp.transformed(trafo);
}

Lattice LatticeUtils::createBCTLattice(double a, double c, const ILatticeOrientation& orientation)
{
    const Lattice prim_tetragonal = Lattice::createTetragonalLattice(1.0, c / a);
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_tetragonal);
    const Transform3D trafo = P_orientation->transformation();
    const Lattice hcp = Lattice::createBCTLattice(a, c);
    return hcp.transformed(trafo);
}
