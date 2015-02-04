/*

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobItem.h
//! @brief     Defines class JobItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBITEM_H
#define JOBITEM_H

#include "WinDllMacros.h"
#include <QList>
#include <QVariant>
#include <QString>
#include <QStringList>

class OutputDataItem;
class SampleModel;
class InstrumentModel;
class QXmlStreamWriter;
class QXmlStreamReader;
class Simulation;


//! Class to hold all job settings
//!
//! See also JobQueueItem which is stored in a list by JobQueueModel and serve
//! as an adapter for given JobItem.
class BA_CORE_API_ JobItem : public QObject
{
    Q_OBJECT

public:
    enum EJobStatus { IDLE, RUNNING, COMPLETED, CANCELLED, FAILED };

    enum ERunPolicy {
        RUN_IMMEDIATELY = 0x0001,
        RUN_IN_BACKGROUND  = 0x0002,
        SUBMIT_ONLY = 0x0004
    };

    JobItem(const QString &name);
    JobItem(SampleModel *sampleModel, InstrumentModel *instrumentModel,
            const QString &run_policy = QString());

    virtual ~JobItem();

    QString getName() const { return m_name; }

    QString getBeginTime() const { return m_begin_time; }

    QString getEndTime() const { return m_end_time; }

    QString getComments() const { return m_comments; }

    EJobStatus getStatus() const { return m_status; }

    QString getStatusString() const;

    int getProgress() const { return m_progress; }

    void writeTo(QXmlStreamWriter *writer);
    void readFrom(QXmlStreamReader *reader);

    bool isRunning() const { return m_status == RUNNING; }

    OutputDataItem *getOutputDataItem(int n_item = 0);

    ERunPolicy getRunPolicy() const { return m_run_policy; }
    void setRunPolicy(ERunPolicy run_policy) { m_run_policy = run_policy; }
    void setRunPolicy(const QString &run_policy);

    SampleModel *getSampleModel();
    void setSampleModel(SampleModel *sampleModel);

    InstrumentModel *getInstrumentModel();
    void setInstrumentModel(InstrumentModel *instrumentModel);

    static QMap<QString, QString> getRunPolicies() { return m_run_policies; }

    void initOutputDataItem();

    void setResults(const Simulation *simulation);

    int getNumberOfThreads() const { return m_nthreads; }
    void setNumberOfThreads(int nthreads) { m_nthreads = nthreads; }

signals:
    void modified(JobItem *);

public slots:
    void setName(QString name);
    void setBeginTime(QString begin_time) {
        m_begin_time = begin_time;
        emit modified(this);
    }
    void setEndTime(QString end_time) {
        m_end_time = end_time;
        emit modified(this);
    }
    void setComments(QString comments) {
        m_comments = comments;
        emit modified(this);
    }
    void setStatus(EJobStatus status) {
        m_status = status;
        emit modified(this);
    }
    void setProgress(int progress) {
        m_progress = progress;
        emit modified(this);
    }

    void onDataItemModified() {
        emit modified(this);
    }

private:
    void clear();

    QString m_name;
    QString m_begin_time;
    QString m_end_time;
    QString m_comments;
    EJobStatus m_status;
    int m_progress;
    int m_nthreads;

    QList<OutputDataItem *> m_data_items;
    ERunPolicy m_run_policy;

    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;

    static QStringList m_status_list;
    static QMap<QString, QString> m_run_policies; // run policy, policy description
};



#endif // JOBITEM_H

*/
