// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SimulationWidgets/SimulationSetupWidget.h
//! @brief     Defines class SimulationSetupWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONSETUPWIDGET_H
#define SIMULATIONSETUPWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QString>

class QComboBox;
class QPushButton;
class QLabel;
class ProjectManager;
class MultiLayerItem;
class InstrumentItem;
class SimulationOptionsWidget;
class ApplicationModels;

class TestItem {
public:
    int x;
};

class BA_CORE_API_ SimulationSetupWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationSetupWidget(QWidget *parent = 0);

    void setApplicationModels(ApplicationModels *model);
    void setProjectManager(ProjectManager *projectManager);
    void updateViewElements();

    QString getSelectedInstrumentName() const;
    int getSelectedInstrumentIndex() const;

    QString getSelectedSampleName() const;
    int getSelectedSampleIndex() const;

public slots:
    void onRunSimulation();
    void onExportToPythonScript();
    void onOpenFile();

private:
    void updateSelectionBox(QComboBox *comboBox, QStringList itemList);

    const MultiLayerItem *getSelectedMultiLayerItem() const;
    const InstrumentItem *getSelectedInstrumentItem() const;

    bool isValidSetup(const MultiLayerItem *multiLayerItem, const InstrumentItem *instrumentItem);

    QWidget *createDataSelectorWidget();
    QWidget *createButtonWidget();

    ApplicationModels *m_applicationModels;
    ProjectManager *m_projectManager;

    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *runSimulationButton;
    QPushButton *selectRealData;
    QLabel *pathLabel;
    QPushButton *exportToPyScriptButton;

    SimulationOptionsWidget *m_simOptionsWidget;

    QVector<TestItem *> testitems;

};

#endif // SIMULATIONSETUPWIDGET_H
