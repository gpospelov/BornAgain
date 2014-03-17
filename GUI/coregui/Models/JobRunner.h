#ifndef JOBRUNNER_H
#define JOBRUNNER_H

#include <QObject>
class Simulation;

//! Class for running the simulation in a thread
class JobRunner : public QObject
{
    Q_OBJECT
public:

    JobRunner(Simulation *simulation);
    virtual ~JobRunner();

public slots:
    void run();
    void terminate();

private slots:
    void loopFunctionWithDelay();

signals:
    void finished();
    void progressUpdate(int);

private:
    Simulation *m_simulation;
    int m_progress;

};



#endif // JOBRUNNER_H

