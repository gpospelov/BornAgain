// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobOutputDataToolBar.h
//! @brief     Declares class JobOutputDataToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBOUTPUTDATATOOLBAR_H
#define JOBOUTPUTDATATOOLBAR_H

#include "StyledToolBar.h"

class QToolButton;

//! The JobOutputDataToolBar class represents main toolbar of JobOutputDataWidget.

class BA_CORE_API_ JobOutputDataToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit JobOutputDataToolBar(QWidget *parent = 0);

signals:
    void togglePropertyPanel();
    void toggleProjections();
    void resetView();
    void savePlot();

private:
    QToolButton *m_toggleProjectionsButton;
    QToolButton *m_togglePropertyPanelButton;
    QToolButton *m_resetViewButton;
    QToolButton *m_savePlotButton;
};

#endif
