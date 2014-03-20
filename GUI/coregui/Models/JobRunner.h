#ifndef JOBRUNNER_H
#define JOBRUNNER_H

#include <QObject>
#include <QString>

class Simulation;

//! Class for running the simulation in a thread
class JobRunner : public QObject
{
    Q_OBJECT
public:

    JobRunner(QString identifier, Simulation *simulation = 0);
    virtual ~JobRunner();

    QString getIdentifier() const { return m_identifier; }
    void setIdentifier(QString identifier) { m_identifier = identifier; }

    int getProgress() const { return m_progress; }

    bool similationProgressCallback(int);

signals:
    void started();
    void finished();
    void progressUpdate();

public slots:
    void start();
    void terminate();

private slots:
    void runFakeSimulation();

private:
    QString m_identifier;
    Simulation *m_simulation;
    int m_progress;
    int m_run_flag;
};



#endif // JOBRUNNER_H

