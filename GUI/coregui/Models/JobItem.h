#ifndef JOBITEM_H
#define JOBITEM_H

#include <QList>
#include <QVariant>
#include <QString>
#include <QStringList>

class QXmlStreamWriter;
class QXmlStreamReader;
class OutputDataItem;


//! Class to hold all job settings
//!
//! See also JobQueueItem which is stored in a list by JobQueueModel and serve
//! as an adapter for given JobItem.
class JobItem : public QObject
{
    Q_OBJECT

public:
    enum JobStatus
    {
        Idle,
        Running,
        Completed,
        Canceled
    };

    enum RunPolicy
    {
        SubmitOnly = 0x0001,
        RunImmediately = 0x0002,
        RunInBackground  = 0x0004
    };

    JobItem(QString name);
    virtual ~JobItem();

    QString getName() const { return m_name; }

    QString getBeginTime() const { return m_begin_time; }

    QString getEndTime() const { return m_end_time; }

    QString getComments() const { return m_comments; }

    JobStatus getStatus() const { return m_status; }

    QString getStatusString() const;

    int getProgress() const { return m_progress; }

    void writeTo(QXmlStreamWriter *writer);
    void readFrom(QXmlStreamReader *reader);

    bool isRunning() const { return m_status == Running; }

    OutputDataItem *getOutputDataItem(int n_item = 0);

    RunPolicy getRunPolicy() const { return m_run_policy; }
    void setRunPolicy(RunPolicy run_policy) { m_run_policy = run_policy; }

signals:
    void modified(JobItem *);

public slots:
    void setName(QString name);
    void setBeginTime(QString begin_time) { m_begin_time = begin_time; emit modified(this);}
    void setEndTime(QString end_time) { m_end_time = end_time; emit modified(this);}
    void setComments(QString comments) { m_comments = comments; emit modified(this);}
    void setStatus(JobStatus status) { m_status = status; emit modified(this);}
    void setProgress(int progress) { m_progress = progress; emit modified(this); }

    void onDataItemModified() { emit modified(this); }

private:
    void clear();

    QString m_name;
    QString m_begin_time;
    QString m_end_time;
    QString m_comments;
    JobStatus m_status;
    int m_progress;

    QList<OutputDataItem *> m_data_items;
    QStringList m_status_list;
    RunPolicy m_run_policy;
};



#endif // JOBITEM_H
