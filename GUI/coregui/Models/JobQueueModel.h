#ifndef JOBQUEUEMODEL_H
#define JOBQUEUEMODEL_H

#include <QStandardItemModel>

class JobQueueModel : public QStandardItemModel
{
    Q_OBJECT
    public:
    explicit JobQueueModel(QObject *parent = 0);

};



#endif
