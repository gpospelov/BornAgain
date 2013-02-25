#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QWidget>

class SimulationDataModel;
class QComboBox;
class QPushButton;

class SimulationView : public QWidget
{
    Q_OBJECT

public:
    SimulationView(SimulationDataModel *p_simulation_data_model, QWidget *parent = 0);
    void updateViewElements();

public slots:
    void onRunSimulation();

private:
    SimulationDataModel *mp_simulation_data_model;
    QComboBox *instrumentSelectionBox;
    QComboBox *sampleSelectionBox;
    QPushButton *runSimulationButton;
};

#endif // SIMULATIONVIEW_H
