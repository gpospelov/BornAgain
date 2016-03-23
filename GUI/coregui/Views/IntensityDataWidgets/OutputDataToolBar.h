// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/OutputDataToolBar.h
//! @brief     Defines class OutputDataToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATATOOLBAR_H
#define OUTPUTDATATOOLBAR_H

#include <QToolBar>
#include "WinDllMacros.h"

class QAction;
class QToolButton;
class QToolBar;

//! main tool bar of OutputDataWidget
class BA_CORE_API_ OutputDataToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit OutputDataToolBar(QWidget *parent = 0);

signals:
    void togglePropertyPanel();
    void toggleProjections();
    void resetView();
    void savePlot();

private:
    QToolButton *m_togglePropertyPanelButton;
    QToolButton *m_toggleProjectionsButton;
    QToolButton *m_resetViewButton;
    QToolButton *m_savePlotButton;

};


#endif // OUTPUTDATATOOLBAR_H
