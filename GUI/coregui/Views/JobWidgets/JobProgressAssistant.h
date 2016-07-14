// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobProgressAssistant.h
//! @brief     Declares class JobProgressAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBPROGRESSASSISTANT_H
#define JOBPROGRESSASSISTANT_H

#include <QObject>
#include "WinDllMacros.h"

class MainWindow;

//! The JobProgressAssistant class helps JobView to visualize current progress.

class BA_CORE_API_ JobProgressAssistant : public QObject
{
    Q_OBJECT
public:
    JobProgressAssistant(MainWindow *mainWindow);

private slots:
    void onGlobalProgress(int progress);

private:
    MainWindow *m_mainWindow;
};

#endif // JOBPROGRESSASSISTANT_H
