#ifndef JOBRUNNER_H
#define JOBRUNNER_H

#include <QObject>
#include <QString>

//! Class for running the simulation in a thread
class JobRunner : public QObject
{
    Q_OBJECT
public:

    JobRunner(QString identifier);
    virtual ~JobRunner();

    QString getIdentifier() const { return m_identifier; }
    void setIdentifier(QString identifier) { m_identifier = identifier; }

    int getProgress() const { return m_progress; }

signals:
    void started();
    void finished();
    void progressUpdate();

public slots:
    void start();
    void terminate();

private slots:
    void loopFunctionWithDelay();

private:
    QString m_identifier;
    int m_progress;

};



#endif // JOBRUNNER_H

