// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationOptionsWidget.h
//! @brief     Declares class SimulationOptionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONOPTIONSWIDGET_H
#define SIMULATIONOPTIONSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class SimulationOptionsItem;
class ComponentBoxEditor;
//class ComponentEditor;

//! Holds widgets related to the setup of simulation/job options (nthreads, run policy,
//! computation method). Part of SimulationView/SimulationSetupWidet

class BA_CORE_API_ SimulationOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationOptionsWidget(QWidget *parent = 0);

    void setItem(SimulationOptionsItem *item);

private:
    ComponentBoxEditor *m_boxEditor;
//    ComponentEditor *m_boxEditor;
};

#endif // SIMULATIONOPTIONSWIDGET_H
