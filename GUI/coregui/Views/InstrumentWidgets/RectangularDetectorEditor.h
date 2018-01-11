// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/RectangularDetectorEditor.h
//! @brief     Defines class RectangularDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef RECTANGULARDETECTOREDITOR_H
#define RECTANGULARDETECTOREDITOR_H

#include "SessionItemWidget.h"
class RectangularDetectorItem;

class BA_CORE_API_ RectangularDetectorEditor : public SessionItemWidget
{
    Q_OBJECT
public:
    RectangularDetectorEditor(QWidget* parent = nullptr);

protected:
    RectangularDetectorItem* detectorItem();

    void subscribeToItem();
    void unsubscribeFromItem();
};

#endif  // RECTANGULARDETECTOREDITOR_H
