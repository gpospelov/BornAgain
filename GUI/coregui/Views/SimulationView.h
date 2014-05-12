#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QWidget>
#include <QString>

class SimulationDataModel;
class QComboBox;
class QPushButton;
class JobQueueModel;

class SimulationView : public QWidget
{
    Q_OBJECT

public:
    SimulationView(SimulationDataModel *p_simulation_data_model, QWidget *parent = 0);
    void updateViewElements();
    void setJobQueueModel(JobQueueModel *model);

public slots:
    void onRunSimulation();
    void onPythonJobLaunched();
    void onJobFinished();

private:
    SimulationDataModel *mp_simulation_data_model;
    JobQueueModel *m_jobQueueModel;
    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *runSimulationButton;
    //QPushButton *runPyScriptSimulation;
};

#endif // SIMULATIONVIEW_H
