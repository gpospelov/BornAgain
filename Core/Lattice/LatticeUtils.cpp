// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LatticeUtils.cpp
//! @brief     Implements factory functions for different types of lattices and orientations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "LatticeUtils.h"
#include "ILatticeOrientation.h"

Lattice LatticeUtils::CreateFCCLattice(double lattice_constant,
                                       const ILatticeOrientation& orientation)
{
    Lattice prim_cubic( {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} );
    std::unique_ptr<ILatticeOrientation> P_orientation(orientation.clone());
    P_orientation->usePrimitiveLattice(prim_cubic);
    auto rotation = P_orientation->transformationMatrix();
    double a = lattice_constant/2.0;
    Lattice fcc( {a, a, 0.0}, {0.0, a, a}, {a, 0.0, a} );
    return fcc.createTransformedLattice(rotation);
}
