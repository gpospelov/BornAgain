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
#include "Rectangle.h"
#include "IntensityDataFunctions.h"
#include "BornAgainNamespace.h"
#include "RegionOfInterest.h"
#include <sstream>

SimulationArea::SimulationArea(const IDetector2D *detector)
    : m_detector(detector)
{
    if(detector == nullptr)
        throw Exceptions::RuntimeErrorException("SimulationArea::SimulationArea -> Error. "
                                                "Detector nullptr.");

    if (m_detector->getDimension()!=2)
        throw Exceptions::RuntimeErrorException(
            "SimulationArea::SimulationArea: detector is not two-dimensional");
}

SimulationAreaIterator SimulationArea::begin()
{
    return SimulationAreaIterator(this, 0);
}

SimulationAreaIterator SimulationArea::end()
{
    return SimulationAreaIterator(this, m_detector->getTotalSize());
}

bool SimulationArea::isMasked(size_t index) const
{
    if(index >= m_detector->getTotalSize()) {
        std::ostringstream message;
        message << "SimulationArea::isActive() -> Error. Index " << index << " is out of range, "
             << "totalSize=" << m_detector->getTotalSize();
        throw Exceptions::RuntimeErrorException(message.str());
    }

    if(m_detector->regionOfInterest())
        if(!m_detector->regionOfInterest()->isInROI(index)) return true;

    return m_detector->isMasked(index);
}

size_t SimulationArea::totalSize() const
{
    return m_detector->getTotalSize();
}

size_t SimulationArea::roiIndex(size_t globalIndex) const
{
    if(!m_detector->regionOfInterest())
        return globalIndex;

    return m_detector->regionOfInterest()->roiIndex(globalIndex);
}

// --------------------------------------------------------------------------------------

SimulationRoiArea::SimulationRoiArea(const IDetector2D *detector)
    : SimulationArea(detector)
{

}

bool SimulationRoiArea::isMasked(size_t index) const
{
    if(m_detector->regionOfInterest())
        if(!m_detector->regionOfInterest()->isInROI(index)) return true;

    return false;
}
