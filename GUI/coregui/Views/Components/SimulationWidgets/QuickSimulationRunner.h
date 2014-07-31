#ifndef QUICKSIMULATIONRUNNER_H
#define QUICKSIMULATIONRUNNER_H

#include <QObject>

class JobQueueData;
class Simulation;
class JobItem;
class PlotWidget;

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

    void setPlotWidget(PlotWidget *plotWidget);

public slots:
    void onJobItemIsModified(JobItem *);
    void onFinishedJob(const QString &identifier);

private:
    JobQueueData *m_jobQueueData;
    PlotWidget *m_plotWidget;
    bool m_simulation_in_progress;
};


#endif
