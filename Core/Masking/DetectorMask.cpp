// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/DetectorMask.cpp
//! @brief     Implements class DetectorMask.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BornAgainNamespace.h"
#include "IDetector2D.h"


// InfinitePlane, Line, VerticalLine, HorizontalLine

DetectorMask::DetectorMask()
    : m_number_of_masked_channels(0)
{
}

DetectorMask::DetectorMask(const DetectorMask& other)
    : m_shapes(other.m_shapes)
    , m_mask_of_shape(other.m_mask_of_shape)
    , m_number_of_masked_channels(other.m_number_of_masked_channels)
{
    m_mask_data.copyFrom(other.m_mask_data);
}

DetectorMask& DetectorMask::operator=(const DetectorMask& other)
{
    if (this != &other) {
        m_shapes = other.m_shapes;
        m_mask_of_shape = other.m_mask_of_shape;
        m_mask_data.copyFrom(other.m_mask_data);
        m_number_of_masked_channels = other.m_number_of_masked_channels;
//        DetectorMask tmp(other);
//        tmp.swapContent(*this);
    }
    return *this;
}

void DetectorMask::addMask(const Geometry::IShape2D& shape, bool mask_value)
{
    m_shapes.push_back(shape.clone());
    m_mask_of_shape.push_back(mask_value);
    m_mask_data.clear();
    m_number_of_masked_channels = 0;
}

void DetectorMask::initMaskData(const IDetector2D& detector)
{
    assert(m_shapes.size() == m_mask_of_shape.size());
    m_mask_data.clear();

    for (size_t dim=0; dim<detector.getDimension(); ++dim)
        m_mask_data.addAxis(detector.getAxis(dim));

    process_masks();
}

void DetectorMask::initMaskData(const OutputData<double>& data)
{
    assert(m_shapes.size() == m_mask_of_shape.size());
    m_mask_data.clear();

    for (size_t dim=0; dim<data.getRank(); ++dim)
        m_mask_data.addAxis(*data.getAxis(dim));

    process_masks();
}

bool DetectorMask::getMask(size_t index) const
{
    if(!m_mask_data.isInitialized())
        throw Exceptions::LogicErrorException(
            "DetectorMask::getMask() -> Error. Masks are not initialized");
    return m_mask_data[index];
}

const OutputData<bool>* DetectorMask::getMaskData() const
{
    return &m_mask_data;
}

void DetectorMask::removeMasks()
{
    m_shapes.clear();
    m_mask_of_shape.clear();
    m_mask_data.clear();
}

bool DetectorMask::hasMasks() const
{
    return m_shapes.size() ? true : false;
}

int DetectorMask::getNumberOfMaskedChannels() const
{
    return m_number_of_masked_channels;
}

size_t DetectorMask::getNumberOfMasks() const
{
    return m_shapes.size();
}

const Geometry::IShape2D* DetectorMask::getMaskShape(size_t mask_index, bool& mask_value) const
{
    if(mask_index < getNumberOfMasks()) {
        mask_value = m_mask_of_shape[mask_index];
        return m_shapes[mask_index];
    }
    return 0;
}

void DetectorMask::process_masks()
{
    m_mask_data.setAllTo(false);
    if(!m_shapes.size()) return;

    m_number_of_masked_channels = 0;
    for(size_t index=0; index<m_mask_data.getAllocatedSize(); ++index) {
        Bin1D binx = m_mask_data.getAxisBin(index, BornAgain::X_AXIS_INDEX);
        Bin1D biny = m_mask_data.getAxisBin(index, BornAgain::Y_AXIS_INDEX);
        // setting mask to the data starting from last shape added
        bool is_masked(false);
        for(size_t i_shape=m_shapes.size(); i_shape>0; --i_shape) {
            const Geometry::IShape2D* shape = m_shapes[i_shape-1];
            if(shape->contains(binx, biny)) {
                if(m_mask_of_shape[i_shape-1]) is_masked = true;
                m_mask_data[index] = m_mask_of_shape[i_shape-1];
                // if given index is covered by the shape, stop looking further
                break;
            }
        }
        if(is_masked) ++m_number_of_masked_channels;
    }
}
