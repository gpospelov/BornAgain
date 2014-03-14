#ifndef JOBQUEUEMODEL_H
#define JOBQUEUEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QMap>


class JobQueueItem;
class QXmlStreamWriter;
class QXmlStreamReader;
class QItemSelection;
class QThread;

namespace JobQueueXML
{
    const QString ModelTag("JobQueueModel");
    const QString ModelNameAttribute("Name");
    const QString JobTag("Job");
    const QString JobNameAttribute("Name");
    const QString JobBeginTimeAttribute("BeginTime");
    const QString JobEndTimeAttribute("EndTime");
    const QString JobCommentsAttribute("Comments");
    const QString JobStatusAttribute("Status");
    const QString OutputDataTag("OutputData");
    const QString OutputDataNameAttribute("Name");
    const QString OutputDataXminAttribute("Xmin");
    const QString OutputDataXmaxAttribute("Xmax");
    const QString OutputDataYminAttribute("Ymin");
    const QString OutputDataYmaxAttribute("Ymax");
    const QString OutputDataZminAttribute("Zmin");
    const QString OutputDataZmaxAttribute("Zmax");
    const QString OutputDataLogzAttribute("Logz");
    const QString OutputDataInterpolatedAttribute("Interpolated");
}


class JobQueueModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit JobQueueModel(QObject *parent = 0);
    virtual ~JobQueueModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

//    bool insertRows(int position, int rows, const QModelIndex &parent);
    bool removeRows(int position, int rows, const QModelIndex &parent);

    Qt::DropActions supportedDragActions() const { return Qt::MoveAction; }
    Qt::DropActions supportedDropActions() const { return Qt::MoveAction; }

    QStringList mimeTypes() const;

    QMimeData *mimeData(const QModelIndexList &indexes) const;

    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);


    void addJob(JobQueueItem *item);

    void clear();

    void save(const QString &filename=QString());
    void writeTo(QXmlStreamWriter *writer);

    void load(const QString &filename=QString());
    void readFrom(QXmlStreamReader *reader);

    QString getName() const { return m_name; }
    void setName(QString name) { m_name = name; }

    JobQueueItem *getJobQueueItemForIndex(const QModelIndex &index);
    const JobQueueItem *getJobQueueItemForIndex(const QModelIndex &index) const;


    void runInThread(JobQueueItem *job);

public slots:
    void jobQueueItemIsChanged(JobQueueItem *item);
    void onSelectionChanged( const QItemSelection&, const QItemSelection& );

    void onCancelJob(const QModelIndex &index);

signals:
    void selectionChanged(JobQueueItem *item);

private:
    QModelIndex indexOfItem(JobQueueItem *item) const;

    QString m_name;
    QList <JobQueueItem *> m_jobs;

    QMap<JobQueueItem *, QThread *> m_JobQueueItemToThread;
    QMap<QThread *, JobQueueItem *> m_ThreadToJobQueueItem;
};


#endif
