// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobListToolBar.cpp
//! @brief     Implements class JobListToolBar
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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

