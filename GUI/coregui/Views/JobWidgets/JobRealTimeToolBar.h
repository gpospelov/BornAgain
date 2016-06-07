// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobRealTimeToolBar.h
//! @brief     Declares class JobRealTimeToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBREALTIMETOOLBAR_H
#define JOBREALTIMETOOLBAR_H

#include "StyledToolBar.h"

//! The JobRealTimeToolBar class represents a toolbar with buttons for JobRealTimeWidget.

class BA_CORE_API_ JobRealTimeToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit JobRealTimeToolBar(QWidget *parent = 0);

signals:
    void resetParameters();

private:
    class QToolButton *m_resetParametersButton;
};

#endif

