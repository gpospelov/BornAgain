// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskDrawingContext.h
//! @brief     Defines class MaskDrawingContext
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKDRAWINGCONTEXT_H
#define MASKDRAWINGCONTEXT_H

#include "MaskEditorFlags.h"
#include "WinDllMacros.h"

//! Helper class for MaskGraphicsScene to hold drawing conditions

class BA_CORE_API_ MaskDrawingContext
{
public:
    MaskDrawingContext();

    MaskEditorFlags::Activity getActivityType() const;
    void setActivityType(MaskEditorFlags::Activity value);
    void setMaskValue(MaskEditorFlags::MaskValue value);

    bool isSelectionMode() const;
    bool isInZoomMode() const;
    bool isRectangleShapeMode() const;
    bool isRectangleMode() const;
    bool isEllipseMode() const;
    bool isPolygonMode() const;
    bool isLineMode() const;
    bool isVerticalLineMode() const;
    bool isHorizontalLineMode() const;
    bool isMaskAllMode() const;
    bool isROIMode() const;

    bool isDrawingInProgress() const;
    void setDrawingInProgress(bool value);

    bool getMaskValue() const;

    bool isActivityRequiresDrawingCancel(MaskEditorFlags::Activity proposed_new_activity);

    QString activityToModelType() const;
    int activityToRow() const;

private:

    MaskEditorFlags::Activity m_current_activity;
    MaskEditorFlags::MaskValue m_mask_value;
    bool m_drawing_in_progress;
};


#endif // MASKDRAWINGCONTEXT_H
