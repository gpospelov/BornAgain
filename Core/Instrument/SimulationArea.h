// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationArea.h
//! @brief     Defines class SimulationArea.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONAREA_H
#define SIMULATIONAREA_H

#include "WinDllMacros.h"
#include "SimulationAreaIterator.h"
class IDetector2D;

//! @class SimulationArea
//! @ingroup simulation
//! @brief The SimulationArea class holds iteration logic over active detector channels
//! in the presence of masked areas and RegionOfInterest defined.

class BA_CORE_API_ SimulationArea
{
public:
    using iterator = SimulationAreaIterator;
    explicit SimulationArea(const IDetector2D *detector);

    SimulationAreaIterator begin();
    SimulationAreaIterator end();

    const IDetector2D* detector() const { return m_detector; }

private:
    const IDetector2D *m_detector;
};


#endif
