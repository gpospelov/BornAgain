#ifndef JOBMODEL_H
#define JOBMODEL_H

#include <QThread>
#include <QString>

class Simulation;
class TH2D;

class JobModel : public QThread
{
    Q_OBJECT

public:
    JobModel(Simulation *p_simulation);
    virtual ~JobModel();

    QString getName() const { return m_name; }

    TH2D *getHistogram();

protected:
    void run();
    QString getJobTimeStamp() const;
    QString m_name;
    Simulation *mp_simulation;
    bool m_isFinished;
};

#endif // JOBMODEL_H
