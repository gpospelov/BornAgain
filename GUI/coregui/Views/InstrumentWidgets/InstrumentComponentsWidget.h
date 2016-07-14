// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentComponentsWidget.h
//! @brief     Declares class InstrumentComponentsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTCOMPONENTSWIDGET_H
#define INSTRUMENTCOMPONENTSWIDGET_H

#include <QWidget>
#include "WinDllMacros.h"

class BeamItem;
class DetectorItem;
class BeamEditorWidget;
class DetectorEditorWidget;
class ColumnResizer;

class BA_CORE_API_ InstrumentComponentsWidget : public QWidget
{
    Q_OBJECT
public:
    InstrumentComponentsWidget(QWidget *parent = 0);

    void setBeamItem(BeamItem *beamItem);
    void setDetectorItem(DetectorItem *detectorItem);

signals:
    void extendedDetectorEditorRequest(DetectorItem *);

private:
    ColumnResizer *m_columnResizer;
    BeamEditorWidget *m_beamEditor;
    DetectorEditorWidget *m_detectorEditor;
    BeamItem *m_beamItem;
    DetectorItem *m_detectorItem;
};

#endif // INSTRUMENTCOMPONENTSWIDGET_H
