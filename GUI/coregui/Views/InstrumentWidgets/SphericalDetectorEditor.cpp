// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SphericalDetectorEditor.cpp
//! @brief     Implement class SphericalDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SphericalDetectorEditor.h"
#include "SphericalDetectorItem.h"

SphericalDetectorEditor::SphericalDetectorEditor(QWidget* parent)
    : SessionItemWidget(parent)
{

}

SphericalDetectorItem* SphericalDetectorEditor::detectorItem()
{
    auto result = dynamic_cast<SphericalDetectorItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

void SphericalDetectorEditor::subscribeToItem()
{

}

void SphericalDetectorEditor::unsubscribeFromItem()
{

}
