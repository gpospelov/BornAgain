// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidgetActions.h
//! @brief     Declares class IntensityDataWidgetActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAWIDGETACTIONS_H
#define INTENSITYDATAWIDGETACTIONS_H

#include "WinDllMacros.h"
#include <QObject>

class QAction;

//! The IntensityDataWidgetActions class holds all actions related to IntensityDataWidget

class BA_CORE_API_ IntensityDataWidgetActions : public QObject
{
    Q_OBJECT

public:
    explicit IntensityDataWidgetActions(QObject *parent);

    QList<QAction *> actionList();

signals:
    void togglePropertyPanel();
    void toggleProjections();
    void resetView();
    void savePlot();

private:
    QAction *m_toggleProjectionsAction;
    QAction *m_togglePropertyPanelAction;
    QAction *m_resetViewAction;
    QAction *m_savePlotAction;
};

#endif
