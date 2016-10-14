// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationArea.cpp
//! @brief     Implements class SimulationArea.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationArea.h"
#include "IDetector2D.h"
#include "Exceptions.h"

SimulationArea::SimulationArea(const IDetector2D *detector)
    : m_detector(detector)
{
    if(detector == nullptr)
        throw Exceptions::RuntimeErrorException("SimulationArea::SimulationArea -> Error. "
                                                "Detector nullptr.");
}

SimulationAreaIterator SimulationArea::begin()
{
    return SimulationAreaIterator(this, 0);
}

SimulationAreaIterator SimulationArea::end()
{
    return SimulationAreaIterator(this, m_detector->getTotalSize());
}

