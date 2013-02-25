#ifndef JOBMODEL_H
#define JOBMODEL_H

#include <QThread>

class Simulation;

class JobModel : public QThread
{
    Q_OBJECT

public:
    JobModel(Simulation *p_simulation);
    virtual ~JobModel();

protected:
    void run();
    Simulation *mp_simulation;
};

#endif // JOBMODEL_H
