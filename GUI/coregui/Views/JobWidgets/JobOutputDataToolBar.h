// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobOutputDataToolBar.h
//! @brief     Defines class JobOutputDataToolBar
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

#include <QToolBar>
#include "WinDllMacros.h"

class QComboBox;
class QToolButton;

//! Main tool bar of JobView widget. Belongs to JobOutputDataWidget.
class BA_CORE_API_ JobOutputDataToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit JobOutputDataToolBar(QWidget *parent = 0);

signals:
    void togglePropertyPanel();
    void toggleProjections();
    void resetView();
    void savePlot();
    void jobViewActivityRequest(int);

public slots:
    void onActivityChanged(int);

private slots:
    void onActivityChangeRequest(const QString &name);

private:
    QComboBox *m_activityCombo;
    QToolButton *m_toggleProjectionsButton;
    QToolButton *m_togglePropertyPanelButton;
    QToolButton *m_resetViewButton;
    QToolButton *m_savePlotButton;
};

#endif
