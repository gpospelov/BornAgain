#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <QWidget>

class SimulationDataModel;
class QComboBox;
class QPushButton;

class SimulationManager : public QWidget
{
    Q_OBJECT

public:
    SimulationManager(SimulationDataModel *p_simulation_data_model, QWidget *parent = 0);
    void updateViewElements();

public slots:
    void onRunSimulation();

private:
    SimulationDataModel *mp_simulation_data_model;
    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *runSimulationButton;
};

#endif // SIMULATIONMANAGER_H
