// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentComponentsWidget.h
//! @brief     Defines class InstrumentComponentsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INSTRUMENTCOMPONENTSWIDGET_H
#define INSTRUMENTCOMPONENTSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class GISASInstrumentItem;
class ComponentEditor;
class DetectorItem;
class BeamEditorWidget;
class DetectorEditorWidget;
class ColumnResizer;

class BA_CORE_API_ InstrumentComponentsWidget : public QWidget
{
    Q_OBJECT
public:
    InstrumentComponentsWidget(QWidget* parent = 0);

    void setInstrumentItem(GISASInstrumentItem* instrumentItem);

signals:
    void extendedDetectorEditorRequest(DetectorItem*);

private:
    ColumnResizer* m_columnResizer;
    BeamEditorWidget* m_beamEditor;
    DetectorEditorWidget* m_detectorEditor;
    ComponentEditor* m_backgroundEditor;
};

#endif // INSTRUMENTCOMPONENTSWIDGET_H
