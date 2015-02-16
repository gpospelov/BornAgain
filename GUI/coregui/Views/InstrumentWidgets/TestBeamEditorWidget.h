// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/TestBeamEditorWidget.h
//! @brief     Defines class TestBeamEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTBEAMEDITORWIDGET_H
#define TESTBEAMEDITORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class BA_CORE_API_ TestBeamEditorWidget : public QWidget
{
    Q_OBJECT
public:
    TestBeamEditorWidget(QWidget *parent = 0);

};

#endif
