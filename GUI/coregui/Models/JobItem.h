#ifndef JOBITEM_H
#define JOBITEM_H

#include <QObject>

class JobItem : public QObject
{
    Q_OBJECT
public:

    JobItem();
    virtual ~JobItem();

public slots:
    void run();

private slots:
    void loopFunctionWithDelay();

signals:
    void finished();

private:

    int m_counterForDelayedLoop;

};



#endif

