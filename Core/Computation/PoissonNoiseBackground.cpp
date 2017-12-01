// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/PoissonNoiseBackground.cpp
//! @brief     Implements class PoissonNoiseBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PoissonNoiseBackground.h"
#include "MathFunctions.h"
#include "SimulationElement.h"

PoissonNoiseBackground::PoissonNoiseBackground()
{
    setName(BornAgain::PoissonNoiseBackgroundType);
}

PoissonNoiseBackground::~PoissonNoiseBackground() =default;

PoissonNoiseBackground*PoissonNoiseBackground::clone() const
{
    return new PoissonNoiseBackground;
}

void PoissonNoiseBackground::addBackGround(std::vector<SimulationElement>::iterator start,
                                           std::vector<SimulationElement>::iterator end) const
{
    for (auto it=start; it != end; it++) {
        auto intensity = it->getIntensity();
        it->setIntensity(MathFunctions::GeneratePoissonRandom(intensity));
    }
}
