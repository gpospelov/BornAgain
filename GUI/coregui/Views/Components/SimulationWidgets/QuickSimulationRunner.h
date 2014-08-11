#ifndef QUICKSIMULATIONRUNNER_H
#define QUICKSIMULATIONRUNNER_H

#include <QObject>

class JobQueueData;
class Simulation;
class JobItem;
class OutputDataWidget;

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

    void setOutputDataWidget(OutputDataWidget *outputDataWidget);

public slots:
    void onJobItemIsModified(JobItem *);
    void onFinishedJob(const QString &identifier);

private:
    JobQueueData *m_jobQueueData;
    OutputDataWidget *m_outputDataWidget;
    bool m_simulation_in_progress;

    QString m_current_identifier;
};


#endif
