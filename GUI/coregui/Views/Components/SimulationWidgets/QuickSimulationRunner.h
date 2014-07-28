#ifndef QUICKSIMULATIONRUNNER_H
#define QUICKSIMULATIONRUNNER_H

#include <QObject>

class JobQueueData;
class Simulation;
class JobItem;

//! The QuickSimulationRunner class runs the simulation in real time following
//! requests of SampleTuningWidget
class QuickSimulationRunner : public QObject
{
    Q_OBJECT
public:

    QuickSimulationRunner(QObject *parent = 0);
    virtual ~QuickSimulationRunner();

    void runSimulation(Simulation *simulation);

    bool isSimulationInProgress() const;

public slots:
    void onJobItemIsModified(JobItem *);

private:
    JobQueueData *m_jobQueueData;
    bool m_simulation_in_progress;
};


#endif
