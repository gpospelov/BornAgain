// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskDrawingContext.cpp
//! @brief     Implements class MaskDrawingContext
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskDrawingContext.h"
#include <QDebug>


MaskDrawingContext::MaskDrawingContext()
    : m_current_activity(MaskEditorFlags::SELECTION_MODE)
    , m_mask_value(MaskEditorFlags::MASK_ON)
{

}

void MaskDrawingContext::setActivityType(MaskEditorFlags::Activity value)
{
    m_current_activity = value;
}

void MaskDrawingContext::setMaskValue(MaskEditorFlags::MaskValue value)
{
    qDebug() << "MaskDrawingContext::setMaskValue" << value;
    m_mask_value = value;
}

bool MaskDrawingContext::isSelectionMode() const
{
    return m_current_activity.testFlag(MaskEditorFlags::SELECTION_MODE);
}

bool MaskDrawingContext::isInZoomMode() const
{
    return m_current_activity.testFlag(MaskEditorFlags::PAN_ZOOM_MODE);
}

bool MaskDrawingContext::isRectangleMode() const
{
    return m_current_activity.testFlag(MaskEditorFlags::RECTANGLE_MODE);
}

bool MaskDrawingContext::isPolygonMode() const
{
    return m_current_activity.testFlag(MaskEditorFlags::POLYGON_MODE);
}

bool MaskDrawingContext::isLineMode() const
{
    return isVerticalLineMode() || isHorizontalLineMode();
}

bool MaskDrawingContext::isVerticalLineMode() const
{
    return m_current_activity.testFlag(MaskEditorFlags::VERTICAL_LINE_MODE);
}

bool MaskDrawingContext::isHorizontalLineMode() const
{
    return m_current_activity.testFlag(MaskEditorFlags::HORIZONTAL_LINE_MODE);
}

bool MaskDrawingContext::isDrawingInProgress() const
{
    return m_current_activity.testFlag(MaskEditorFlags::DRAWING_IN_PROGRESS);
}

void MaskDrawingContext::setDrawingInProgress(bool value)
{
    if(value) {
        m_current_activity |= MaskEditorFlags::DRAWING_IN_PROGRESS;
    } else {
        m_current_activity &= ~MaskEditorFlags::DRAWING_IN_PROGRESS;
    }
}

bool MaskDrawingContext::getMaskValue() const
{
    return bool(m_mask_value);
}
