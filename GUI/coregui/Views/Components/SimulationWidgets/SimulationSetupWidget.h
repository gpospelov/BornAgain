#ifndef SIMULATIONSETUPWIDGET_H
#define SIMULATIONSETUPWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QString>

class QComboBox;
class QPushButton;
class JobQueueModel;
class SampleModel;
class InstrumentModel;

class BA_CORE_API_ SimulationSetupWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationSetupWidget(QWidget *parent = 0);
    void updateViewElements();
    void setJobQueueModel(JobQueueModel *model);
    void setSampleModel(SampleModel *model);
    void setInstrumentModel(InstrumentModel *model);

    QString getInstrumentSelection() const;
    QString getSampleSelection() const;

public slots:
    void onRunSimulation();
    void onPythonJobLaunched();

private:
    void updateSelectionBox(QComboBox *comboBox, QStringList itemList);

    InstrumentModel *getJobInstrumentModel();
    SampleModel *getJobSampleModel();

    JobQueueModel *m_jobQueueModel;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *runSimulationButton;
    QComboBox *runPolicySelectionBox;
    //QPushButton *runPyScriptSimulation;
};

#endif // SIMULATIONSETUPWIDGET_H
