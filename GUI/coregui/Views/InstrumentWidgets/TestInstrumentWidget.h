// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/TestInstrumentWidget.h
//! @brief     Defines class TestInstrumentWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTINSTRUMENTWIDGET_H
#define TESTINSTRUMENTWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class BeamItem;

class BA_CORE_API_ TestInstrumentWidget : public QWidget
{
    Q_OBJECT
public:
    TestInstrumentWidget(QWidget *parent = 0);

    void setBeamItem(BeamItem *item);

private:
    BeamItem *m_currentItem;
};

#endif
