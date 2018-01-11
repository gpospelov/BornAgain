// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASInstrumentEditor.h
//! @brief     Defines class GISASInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GISASINSTRUMENTEDITOR_H
#define GISASINSTRUMENTEDITOR_H

#include "SessionItemWidget.h"

class GISASInstrumentItem;
class ComponentEditor;
class DetectorItem;
class BeamEditorWidget;
class DetectorEditorWidget;
class ColumnResizer;

class BA_CORE_API_ GISASInstrumentEditor : public SessionItemWidget
{
    Q_OBJECT
public:
    GISASInstrumentEditor(QWidget* parent = 0);

signals:
    void extendedDetectorEditorRequest(DetectorItem*);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    GISASInstrumentItem* instrumentItem();

    ColumnResizer* m_columnResizer;
    BeamEditorWidget* m_beamEditor;
    DetectorEditorWidget* m_detectorEditor;
    ComponentEditor* m_backgroundEditor;
};

#endif // GISASINSTRUMENTEDITOR_H
