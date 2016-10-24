// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/RegionOfInterest.cpp
//! @brief     Implements class RegionOfInterest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RegionOfInterest.h"
#include "Rectangle.h"
#include "IDetector2D.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"

RegionOfInterest::RegionOfInterest(const IDetector2D &detector,
                                   double xlow, double ylow, double xup, double yup)
    : m_rectangle(new Geometry::Rectangle(xlow, ylow, xup, yup))
    , m_ax1(0)
    , m_ay1(0)
    , m_ax2(0)
    , m_ay2(0)
    , m_glob_index0(0)
{
    initFrom(detector);
}

RegionOfInterest *RegionOfInterest::clone() const
{
    return new RegionOfInterest(*this);
}

RegionOfInterest::RegionOfInterest(const RegionOfInterest &other)
    : m_rectangle(other.m_rectangle->clone())
    , m_ax1(other.m_ax1)
    , m_ay1(other.m_ay1)
    , m_ax2(other.m_ax2)
    , m_ay2(other.m_ay2)
    , m_glob_index0(other.m_glob_index0)
    , m_detector_dims(other.m_detector_dims)
    , m_roi_dims(other.m_roi_dims)
{

}

double RegionOfInterest::getXlow() const
{
    return m_rectangle->getXlow();
}

double RegionOfInterest::getYlow() const
{
    return m_rectangle->getYlow();
}

double RegionOfInterest::getXup() const
{
    return m_rectangle->getXup();
}

double RegionOfInterest::getYup() const
{
    return m_rectangle->getYup();
}

size_t RegionOfInterest::detectorIndex(size_t roiIndex) const
{
    std::vector<size_t> coord = coordinates(roiIndex, m_roi_dims);
    return m_glob_index0 + coord[1] + coord[0]*m_detector_dims[1];
}

size_t RegionOfInterest::roiIndex(size_t globalIndex) const
{
    std::vector<size_t> globCoord = coordinates(globalIndex, m_detector_dims);

    if(globCoord[0] < m_ax1 || globCoord[0] > m_ax2)
        throw Exceptions::RuntimeErrorException("RegionOfInterest::roiIndex() -> Error.");

    if(globCoord[1] < m_ay1 || globCoord[1] > m_ay2)
        throw Exceptions::RuntimeErrorException("RegionOfInterest::roiIndex() -> Error.");

    return globCoord[1] - m_ay1 + (globCoord[0] - m_ax1)*m_roi_dims[1];
}

size_t RegionOfInterest::roiSize() const
{
    return m_roi_dims[0]*m_roi_dims[1];
}

size_t RegionOfInterest::detectorSize() const
{
    return m_detector_dims[0]*m_detector_dims[1];
}

void RegionOfInterest::initFrom(const IDetector2D &detector)
{
    if(detector.getDimension() != 2)
        throw Exceptions::RuntimeErrorException("RegionOfInterest::initFrom() -> Error. Detector "
                                                "is not two-dimensional.");

    for(size_t i=0; i<detector.getDimension(); ++i)
        m_detector_dims.push_back(detector.getAxis(i).size());

    m_ax1 = detector.getAxis(BornAgain::X_AXIS_INDEX).findClosestIndex(getXlow());
    m_ax2 = detector.getAxis(BornAgain::X_AXIS_INDEX).findClosestIndex(getXup());
    m_ay1 = detector.getAxis(BornAgain::Y_AXIS_INDEX).findClosestIndex(getYlow());
    m_ay2 = detector.getAxis(BornAgain::Y_AXIS_INDEX).findClosestIndex(getYup());

    m_roi_dims.push_back(m_ax2-m_ax1+1);
    m_roi_dims.push_back(m_ay2-m_ay1+1);

    m_glob_index0 = m_ay1 + m_ax1*m_detector_dims[1];
}
