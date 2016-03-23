// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobListToolBar.cpp
//! @brief     Implements class JobListToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBLISTTOOLBAR_H
#define JOBLISTTOOLBAR_H

#include <QToolBar>
#include "WinDllMacros.h"

class QToolButton;

//! The JobListToolBar contains buttons (add, remove jobs) needed for JobListView
class BA_CORE_API_ JobListToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit JobListToolBar(QWidget *parent = 0);

signals:
    void runJob();
    void removeJob();

private:
    QToolButton *m_runJobButton;
    QToolButton *m_removeJobButton;
};

#endif
