// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/RectangularDetectorEditor.cpp
//! @brief     Implements class RectangularDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RectangularDetectorEditor.h"
#include "RectangularDetectorItem.h"

RectangularDetectorEditor::RectangularDetectorEditor(QWidget* parent)
    : SessionItemWidget(parent)
{

}

RectangularDetectorItem* RectangularDetectorEditor::detectorItem()
{
    auto result = dynamic_cast<RectangularDetectorItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

void RectangularDetectorEditor::subscribeToItem()
{

}

void RectangularDetectorEditor::unsubscribeFromItem()
{

}
