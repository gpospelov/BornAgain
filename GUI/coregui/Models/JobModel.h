#ifndef JOBMODEL_H
#define JOBMODEL_H

#include <QThread>
#include <QString>
#include <QFutureWatcher>

class Simulation;
class TH2D;

class JobModel : public QObject
{
    Q_OBJECT

public:
    JobModel(Simulation *p_simulation);
    virtual ~JobModel();

    QString getName() const { return m_name; }

    QFutureWatcher<void> *getJobWatcher() { return mp_job_watcher; }

    void run();

    TH2D *getHistogram();

public slots:
    void onJobFinished();

protected:
    QString getJobTimeStamp() const;
    QString m_name;
    Simulation *mp_simulation;
    QFutureWatcher<void> *mp_job_watcher;
    bool m_is_finished;
    TH2D *mp_cached_histogram;
};

#endif // JOBMODEL_H
