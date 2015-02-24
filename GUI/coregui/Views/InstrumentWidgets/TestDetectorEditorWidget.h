// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/TestDetectorEditorWidget.h
//! @brief     Defines class TestDetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTDETECTOREDITORWIDGET_H
#define TESTDETECTOREDITORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class TestDetectorItem;
class AwesomePropertyEditor;

class BA_CORE_API_ TestDetectorEditorWidget : public QWidget
{
    Q_OBJECT
public:
    TestDetectorEditorWidget(QWidget *parent = 0);

    void setDetectorItem(TestDetectorItem *detectorItem);

private:
    AwesomePropertyEditor *m_binningEditor;
    AwesomePropertyEditor *m_phiAxisEditor;
    AwesomePropertyEditor *m_alphaAxisEditor;
    TestDetectorItem *m_detectorItem;
};

#endif
