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
class SampleModel;
class InstrumentModel;
class JobModel;
class GISASSimulation;
class ProjectManager;
class MultiLayerItem;
class InstrumentItem;

class BA_CORE_API_ SimulationSetupWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationSetupWidget(QWidget *parent = 0);
    void updateViewElements();
    void setJobModel(JobModel *model);
    void setSampleModel(SampleModel *model);
    void setInstrumentModel(InstrumentModel *model);

    QString getSelectedInstrumentName() const;
    int getSelectedInstrumentIndex() const;

    QString getSelectedSampleName() const;
    int getSelectedSampleIndex() const;

    void setProjectManager(ProjectManager *projectManager);

public slots:
    void onRunSimulation();
    void onExportToPythonScript();

private:
    void updateSelectionBox(QComboBox *comboBox, QStringList itemList);
    QStringList getCPUUsageOptions();
    int getNumberOfThreads();

    InstrumentModel *getJobInstrumentModel();
    SampleModel *getJobSampleModel();

    const MultiLayerItem *getSelectedMultiLayerItem() const;
    const InstrumentItem *getSelectedInstrumentItem() const;

    JobModel *m_jobModel;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *runSimulationButton;
    QComboBox *runPolicySelectionBox;
    QComboBox *cpuUsageSelectionBox;
    QPushButton *exportToPyScriptButton;
    ProjectManager *m_projectManager;
};

#endif // SIMULATIONSETUPWIDGET_H
