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
#include "IDetector.h"
#include "Exceptions.h"
#include "DetectorMask.h"
#include "Rectangle.h"
#include "IntensityDataFunctions.h"
#include "BornAgainNamespace.h"
#include "RegionOfInterest.h"
#include <sstream>

SimulationArea::SimulationArea(const IDetector* detector)
    : m_detector(detector)
    , m_max_index(0)
{
    if (m_detector == nullptr)
        throw std::runtime_error("SimulationArea::SimulationArea: null pointer passed"
                                 " as detector");

    if (m_detector->dimension() == 0)
        throw std::runtime_error(
            "SimulationArea::SimulationArea: detector of unspecified dimensionality");

    if(m_detector->regionOfInterest())
        m_max_index = m_detector->regionOfInterest()->roiSize();
    else
        m_max_index = m_detector->totalSize();
}

SimulationAreaIterator SimulationArea::begin()
{
    return SimulationAreaIterator(this, 0);
}

SimulationAreaIterator SimulationArea::end()
{
    return SimulationAreaIterator(this, totalSize());
}

bool SimulationArea::isMasked(size_t index) const
{
    if(index >= totalSize()) {
        std::ostringstream message;
        message << "SimulationArea::isActive: index " << index << " is out of range, "
                << "total size = " << totalSize();
        throw std::runtime_error(message.str());
    }

    return (m_detector->detectorMask()
            && m_detector->detectorMask()->isMasked(detectorIndex(index)));
}

size_t SimulationArea::roiIndex(size_t index) const
{
    return index;
}

size_t SimulationArea::detectorIndex(size_t index) const
{
    if(!m_detector->regionOfInterest())
        return index;

    return m_detector->regionOfInterest()->detectorIndex(index);
}

// --------------------------------------------------------------------------------------

SimulationRoiArea::SimulationRoiArea(const IDetector *detector)
    : SimulationArea(detector)
{}

bool SimulationRoiArea::isMasked(size_t) const
{
    return false;
}
