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
#include <sstream>

SimulationArea::SimulationArea(const IDetector2D *detector)
    : m_detector(detector)
    , m_roi_x1(0)
    , m_roi_x2(0)
    , m_roi_y1(0)
    , m_roi_y2(0)
{
    if(detector == nullptr)
        throw Exceptions::RuntimeErrorException("SimulationArea::SimulationArea -> Error. "
                                                "Detector nullptr.");

    if (m_detector->getDimension()!=2)
        throw Exceptions::RuntimeErrorException(
            "SimulationArea::SimulationArea: detector is not two-dimensional");

    if(const Geometry::Rectangle *roi = m_detector->regionOfInterest()) {
        m_roi_x1 = detector->getAxis(BornAgain::X_AXIS_INDEX).findClosestIndex(roi->getXlow());
        m_roi_x2 = detector->getAxis(BornAgain::X_AXIS_INDEX).findClosestIndex(roi->getXup());
        m_roi_y1 = detector->getAxis(BornAgain::Y_AXIS_INDEX).findClosestIndex(roi->getYlow());
        m_roi_y2 = detector->getAxis(BornAgain::Y_AXIS_INDEX).findClosestIndex(roi->getYup());
    }
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

    if(m_detector->regionOfInterest()) {
        size_t nx = m_detector->getAxisBinIndex(index, BornAgain::X_AXIS_INDEX);
        if(nx<m_roi_x1 || nx>m_roi_x2) return true;
        size_t ny = m_detector->getAxisBinIndex(index, BornAgain::Y_AXIS_INDEX);
        if(ny<m_roi_y1 || ny>m_roi_y2) return true;
    }

    return m_detector->isMasked(index);
}

size_t SimulationArea::totalSize() const
{
    return m_detector->getTotalSize();
}

int SimulationArea::roiIndex(size_t globalIndex) const
{
    if(!m_detector->regionOfInterest())
        return static_cast<int>(globalIndex);

    size_t nxGlob = m_detector->getAxisBinIndex(globalIndex, BornAgain::X_AXIS_INDEX);
    size_t nyGlob = m_detector->getAxisBinIndex(globalIndex, BornAgain::Y_AXIS_INDEX);
    int nx = nxGlob - m_roi_x1;
    int ny = nyGlob - m_roi_y1;
    if(nx<0 || nx > static_cast<int>(m_roi_x2-m_roi_x1+1)) return -1;
    if(ny<0 || ny > static_cast<int>(m_roi_y2-m_roi_y1+1)) return -1;
    return static_cast<int>(ny + nx*(m_roi_y2-m_roi_y1+1));
}
