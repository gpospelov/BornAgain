#ifndef JOBQUEUEMODEL_H
#define JOBQUEUEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>


class JobQueueItem;
class QXmlStreamWriter;
class QXmlStreamReader;
class QItemSelection;

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


    void addJob(JobQueueItem *item)
    {
        m_jobs.append(item);
    }

    void clear();

    void save(const QString &filename=QString());
    void writeTo(QXmlStreamWriter *writer);

    void load(const QString &filename=QString());
    void readFrom(QXmlStreamReader *reader);

    QString getName() const { return m_name; }
    void setName(QString name) { m_name = name; }

    void jobQueueItemIsChanged(JobQueueItem *item);

public slots:
    void onSelectionChanged( const QItemSelection&, const QItemSelection& );

signals:
    void selectionChanged(JobQueueItem *item);
//    void selectionChanged(const QModelIndex &index);

private:
    QModelIndex indexOfItem(JobQueueItem *item) const;


    QString m_name;
    QList <JobQueueItem *> m_jobs;
};


#endif
