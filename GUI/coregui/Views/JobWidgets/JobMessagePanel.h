// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobMessagePanel.h
//! @brief     Declares class JobMessagePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBMESSAGEPANEL_H
#define JOBMESSAGEPANEL_H

#include "WinDllMacros.h"
#include <QFrame>

class BA_CORE_API_ JobMessagePanel : public QFrame
{
    Q_OBJECT
public:
    JobMessagePanel(QWidget *parent = 0);
};

#endif
