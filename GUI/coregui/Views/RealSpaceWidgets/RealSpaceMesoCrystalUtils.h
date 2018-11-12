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

#ifndef REALSPACEMESOCRYSTALUTILS_H
#define REALSPACEMESOCRYSTALUTILS_H

#include "WinDllMacros.h"
#include "Rotations.h"
#include <QVector3D>

class Particle;
class MesoCrystal;
class MesoCrystalItem;
class Particle3DContainer;

class RealSpaceMesoCrystal
{
public:
    RealSpaceMesoCrystal();
    ~RealSpaceMesoCrystal();

    RealSpaceMesoCrystal(const MesoCrystalItem* mesoCrystalItem, double total_abundance);

    Particle3DContainer populateMesoCrystal(
            const IRotation* extra_rotation = IRotation::createIdentity(),
            kvector_t extra_translation = kvector_t(0, 0, 0));

private:
    const MesoCrystalItem* m_mesoCrystalItem;
    double m_total_abundance;
};

#endif // REALSPACEMESOCRYSTALUTILS_H
