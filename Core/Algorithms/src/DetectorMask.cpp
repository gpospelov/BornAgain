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


// InfinitePlane, Line, VerticalLine, HorizontalLine, Ellipse, Rectangle
//
// copy c-tors for the detector mask as for the detector
//
// Polygon stdvector<stdvector<double>> constructor

void DetectorMask::addMask(const Geometry::IShape2D &shape, bool mask_value)
{
    Geometry::IShape2D *clone = shape.clone();
    m_shapes.push_back(clone);
    m_shape_to_mask[clone] = mask_value;
}

void DetectorMask::initMaskData(const Detector &detector)
{
    m_mask_data.clear();
    if(!m_shapes.size()) return;

    assert(m_shapes.size() == m_shape_to_mask.size());

    for (size_t dim=0; dim<detector.getDimension(); ++dim) {
        m_mask_data.addAxis(detector.getAxis(dim));
    }
    m_mask_data.setAllTo(false);

    // setting mask to the data starting from last shape added
    for(size_t index=0; index<m_mask_data.getAllocatedSize(); ++index) {
        double x = m_mask_data.getAxisValue(index, 0);
        double y = m_mask_data.getAxisValue(index, 1);
        for(size_t i_shape=m_shapes.size(); i_shape>0; --i_shape) {
            const Geometry::IShape2D *shape = m_shapes[i_shape-1];
            if(shape->contains(x, y)) {
                m_mask_data[index] = m_shape_to_mask[shape];
                // if given index is covered by the shape, stop looking further
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
