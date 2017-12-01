// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/PoissonNoiseBackground.h
//! @brief     Defines class PoissonNoiseBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef POISSONNOISEBACKGROUND_H
#define POISSONNOISEBACKGROUND_H

#include "IBackground.h"

//! Class representing Poisson noise on top of the scattered intensity
//!
//! @ingroup simulation

class BA_CORE_API_ PoissonNoiseBackground : public IBackground
{
public:
    PoissonNoiseBackground();
    ~PoissonNoiseBackground();
    PoissonNoiseBackground* clone() const override final;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void addBackGround(std::vector<SimulationElement>::iterator start,
                       std::vector<SimulationElement>::iterator end) const override final;
};

#endif // POISSONNOISEBACKGROUND_H
