// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MesoCrystalBuilder.h
//! @brief     Defines class MesoCrystalBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MESOCRYSTALBUILDER_H
#define MESOCRYSTALBUILDER_H

#include "IMultiLayerBuilder.h"
#include "Complex.h"

class IFormFactor;
class ISample;
class Lattice;
class MesoCrystal;

//! Builds sample: cylindrical mesocrystal composed of spheres in a cubic lattice.
//! @ingroup standard_samples

class BA_CORE_API_ MesoCrystalBuilder : public IMultiLayerBuilder
{
public:
    MesoCrystalBuilder();
    MultiLayer* buildSample() const;
};

#endif // MESOCRYSTALBUILDER_H
