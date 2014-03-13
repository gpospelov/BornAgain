#ifndef JOBQUEUEITEM_H
#define JOBQUEUEITEM_H

#include <QList>
#include <QVariant>
#include <QString>
#include <QFutureWatcher>

class QXmlStreamWriter;
class QXmlStreamReader;
class OutputDataItem;

class JobQueueItem : public QObject
{
    Q_OBJECT

public:
    JobQueueItem(QString name);
    virtual ~JobQueueItem();

    QString getName() const { return m_name; }
    void setName(QString name) { m_name = name; }

    QString getBeginTime() const { return m_begin_time; }
    void setBeginTime(QString begin_time) { m_begin_time = begin_time; }

    QString getEndTime() const { return m_end_time; }
    void setEndTime(QString end_time) { m_end_time = end_time; }

    QString getComments() const { return m_comments; }
    void setComments(QString comments) { m_comments = comments; }

    QString getStatus() const { return m_status; }
    void setStatus(QString status) { m_status = status; }

    void writeTo(QXmlStreamWriter *writer);
    void readFrom(QXmlStreamReader *reader);

    void clear();

    void run();

//    QFutureWatcher<void> *getJobWatcher() { return mp_job_watcher; }

public slots:
    void onJobFinished();
//    void loopFunctionWithDelay();

private:
    QString m_name;
    QString m_begin_time;
    QString m_end_time;
    QString m_comments;
    QString m_status;
    QList<OutputDataItem *> m_data_items;

//    int m_counterForDelayedLoop ;
//    QFutureWatcher<void> *mp_job_watcher;

};



#endif
