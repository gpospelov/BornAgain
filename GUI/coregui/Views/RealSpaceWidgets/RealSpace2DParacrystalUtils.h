// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h
//! @brief     Defines RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACE2DPARACRYSTALUTILS_H
#define REALSPACE2DPARACRYSTALUTILS_H

#include "WinDllMacros.h"
#include <vector>

class InterferenceFunction2DParaCrystal;
class SceneGeometry;

class RealSpace2DParacrystalUtils
{
public:
    RealSpace2DParacrystalUtils();
    ~RealSpace2DParacrystalUtils();

    RealSpace2DParacrystalUtils(const InterferenceFunction2DParaCrystal*,
                                const SceneGeometry*);

    std::vector<std::vector<double>> compute2DParacrystalLatticePositions();

private:
    const InterferenceFunction2DParaCrystal* m_interference2DParacrystal;
    const SceneGeometry* m_sceneGeometry;
};

#endif // REALSPACE2DPARACRYSTALUTILS_H
