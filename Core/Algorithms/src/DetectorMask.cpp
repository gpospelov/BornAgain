// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/DetectorMask.cpp
//! @brief     Implements class DetectorMask.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectorMask.h"
#include "IShape2D.h"
#include "Detector.h"
#include "BornAgainNamespace.h"


// InfinitePlane, Line, VerticalLine, HorizontalLine, Ellipse, Rectangle

DetectorMask::DetectorMask()
{

}

DetectorMask::DetectorMask(const DetectorMask &other)
    : m_shapes(other.m_shapes)
    , m_mask_of_shape(other.m_mask_of_shape)
{
    m_mask_data.copyFrom(other.m_mask_data);
}

DetectorMask &DetectorMask::operator=(const DetectorMask &other)
{
    if (this != &other) {
        DetectorMask tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void DetectorMask::addMask(const Geometry::IShape2D &shape, bool mask_value)
{
    m_shapes.push_back(shape.clone());
    m_mask_of_shape.push_back(mask_value);
    m_mask_data.clear();
}

void DetectorMask::initMaskData(const Detector &detector)
{
    m_mask_data.clear();

    for (size_t dim=0; dim<detector.getDimension(); ++dim) {
        m_mask_data.addAxis(detector.getAxis(dim));
    }
    m_mask_data.setAllTo(false);

    if(!m_shapes.size()) return;
    assert(m_shapes.size() == m_mask_of_shape.size());

    for(size_t index=0; index<m_mask_data.getAllocatedSize(); ++index) {
        Bin1D binx = m_mask_data.getAxisBin(index, BornAgain::X_AXIS_INDEX);
        Bin1D biny = m_mask_data.getAxisBin(index, BornAgain::Y_AXIS_INDEX);
        // setting mask to the data starting from last shape added
        for(size_t i_shape=m_shapes.size(); i_shape>0; --i_shape) {
            const Geometry::IShape2D *shape = m_shapes[i_shape-1];
            //std::cout << " index:" << index << " i_shape:" << i_shape << " number of shapes:" << m_shapes.size() << std::endl;
            if(shape->contains(binx, biny)) {
                m_mask_data[index] = m_mask_of_shape[i_shape-1];
                // if given index is covered by the shape, stop looking further
                //std::cout << " break! mask of shape" << m_mask_of_shape[i_shape-1] << std::endl;
                break;
            }
        }
    }
}

bool DetectorMask::getMask(size_t index)
{
    if(!m_mask_data.isInitialized()) {
        throw LogicErrorException("DetectorMask::getMask() -> Error. Masks are not initialized");
    }
    return m_mask_data[index];
}

const OutputData<bool> *DetectorMask::getMaskData() const
{
    return &m_mask_data;
}

void DetectorMask::clear()
{
    m_shapes.clear();
    m_mask_of_shape.clear();
    m_mask_data.clear();
}

void DetectorMask::swapContent(DetectorMask &other)
{
    std::swap(this->m_shapes, other.m_shapes);
    std::swap(this->m_mask_of_shape, other.m_mask_of_shape);
    this->m_mask_data.copyFrom(other.m_mask_data);
}
