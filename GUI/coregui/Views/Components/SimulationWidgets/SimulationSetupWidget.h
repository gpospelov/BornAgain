// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SimulationWidgets/SimulationSetupWidget.h
//! @brief     Defines class SimulationSetupWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONSETUPWIDGET_H
#define SIMULATIONSETUPWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QString>

class QComboBox;
class QPushButton;
//class JobQueueModel;
class SampleModel;
class InstrumentModel;
class NJobModel;

class BA_CORE_API_ SimulationSetupWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationSetupWidget(QWidget *parent = 0);
    void updateViewElements();
//    void setJobQueueModel(JobQueueModel *model);
    void setJobModel(NJobModel *model);
    void setSampleModel(SampleModel *model);
    void setInstrumentModel(InstrumentModel *model);

    QString getInstrumentSelection() const;
    QString getSampleSelection() const;

public slots:
    void onRunSimulation();
    void onPythonJobLaunched();

private:
    void updateSelectionBox(QComboBox *comboBox, QStringList itemList);
    QStringList getCPUUsageOptions();
    int getNumberOfThreads();

    InstrumentModel *getJobInstrumentModel();
    SampleModel *getJobSampleModel();

//    JobQueueModel *m_jobQueueModel;
    NJobModel *m_jobModel;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *runSimulationButton;
    QComboBox *runPolicySelectionBox;
    QComboBox *cpuUsageSelectionBox;
    //QPushButton *runPyScriptSimulation;
};

#endif // SIMULATIONSETUPWIDGET_H
