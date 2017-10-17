// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorToolBar.h
//! @brief     Defines class JobSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBSELECTORTOOLBAR_H
#define JOBSELECTORTOOLBAR_H

#include "StyledToolBar.h"

class QAction;
class QToolButton;
class JobSelectorActions;

//! Styled tool bar on top of JobSelector with run/remove job buttons.

class BA_CORE_API_ JobSelectorToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit JobSelectorToolBar(JobSelectorActions* actions, QWidget* parent = nullptr);

private:
    QToolButton* m_runJobButton;
    QToolButton* m_removeJobButton;
};

#endif // INSTRUMENTVIEWTOOLBAR_H

