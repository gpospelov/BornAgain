// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobMessagePanel.cpp
//! @brief     Implements class JobMessagePanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobMessagePanel.h"

JobMessagePanel::JobMessagePanel(QWidget *parent)
    : JobPresenter(0, parent)
{
    setWindowTitle(QLatin1String("Message Panel"));
}
