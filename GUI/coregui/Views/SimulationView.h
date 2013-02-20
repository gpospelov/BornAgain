#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <QWidget>

class QPushButton;

class SimulationManager : public QWidget
{
    Q_OBJECT

public:
    SimulationManager(QWidget *parent = 0);

public slots:
    void onRunSimulation();

private:
    QPushButton *runSimulationButton;
};

#endif // SIMULATIONMANAGER_H
