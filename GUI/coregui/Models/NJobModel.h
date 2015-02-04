// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.h
//! @brief     Defines class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef NJOBMODEL_H
#define NJOBMODEL_H

#include "SessionModel.h"
#include "JobQueueData.h"
class NJobItem;
class SampleModel;
class InstrumentModel;

class BA_CORE_API_ NJobModel : public SessionModel
{
    Q_OBJECT

public:
    explicit NJobModel(QObject *parent = 0);
    ~NJobModel();

    JobQueueData *getJobQueueData() { return m_queue_data; }

    const NJobItem *getJobItemForIndex(const QModelIndex &index) const;
    NJobItem *getJobItemForIndex(const QModelIndex &index);

    NJobItem *addJob(SampleModel *sampleModel, InstrumentModel *instrumentModel,
            const QString &run_policy = QString(), int numberOfThreads=-1);

signals:
    void selectionChanged(NJobItem *item);
    void aboutToDeleteJobItem(NJobItem *item);

public slots:
    void runJob(const QModelIndex &index);
    void cancelJob(const QModelIndex &index);
    void removeJob(const QModelIndex &index);

private:
    QString generateJobName();
    QString generateJobIdentifier();

    JobQueueData *m_queue_data;
};

#endif
