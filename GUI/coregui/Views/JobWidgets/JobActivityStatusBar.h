// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobActivityStatusBar.h
//! @brief     Declares class JobActivityStatusBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBACTIVITYSTATUSBAR_H
#define JOBACTIVITYSTATUSBAR_H

#include "WinDllMacros.h"
#include <QWidget>

class QToolButton;
class QComboBox;

//! Narrow status bar at very bottom of JobView to switch between activities

class BA_CORE_API_ JobActivityStatusBar : public QWidget
{
    Q_OBJECT
public:
    JobActivityStatusBar(QWidget *parent = 0);

signals:
    void toggleJobListRequest();
    void changeActivityRequest(int);

public slots:
    void onActivityChanged(int activity);

private:
    QToolButton *m_toggleJobListButton;
    QComboBox *m_activityCombo;
};

#endif
