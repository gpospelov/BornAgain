#ifndef SIMULATIONSETUPWIDGET_H
#define SIMULATIONSETUPWIDGET_H

#include <QWidget>
#include <QString>

class SimulationDataModel;
class QComboBox;
class QPushButton;
class JobQueueModel;

class SimulationSetupWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationSetupWidget(SimulationDataModel *p_simulation_data_model, QWidget *parent = 0);
    void updateViewElements();
    void setJobQueueModel(JobQueueModel *model);

    QString getInstrumentSelection() const;
    QString getSampleSelection() const;

public slots:
    void onRunSimulation();
    void onPythonJobLaunched();
    void onJobFinished();

private:
    void updateSelectionBox(QComboBox *comboBox, QStringList itemList);

    SimulationDataModel *mp_simulation_data_model;
    JobQueueModel *m_jobQueueModel;
    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *runSimulationButton;
    QComboBox *runPolicySelectionBox;
    //QPushButton *runPyScriptSimulation;
};

#endif // SIMULATIONSETUPWIDGET_H
