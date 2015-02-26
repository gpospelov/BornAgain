// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/InstrumentComponentsWidget.h
//! @brief     Defines class InstrumentComponentsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTCOMPONENTSWIDGET_H
#define INSTRUMENTCOMPONENTSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class BeamItem;
class TestDetectorItem;
class TestBeamEditorWidget;
class TestDetectorEditorWidget;

class BA_CORE_API_ InstrumentComponentsWidget : public QWidget
{
    Q_OBJECT
public:
    InstrumentComponentsWidget(QWidget *parent = 0);

    void setBeamItem(BeamItem *beamItem);
    void setDetectorItem(TestDetectorItem *detectorItem);

private:
    TestBeamEditorWidget *m_beamEditor;
    TestDetectorEditorWidget *m_detectorEditor;
    BeamItem *m_beamItem;
    TestDetectorItem *m_detectorItem;
};

#endif
