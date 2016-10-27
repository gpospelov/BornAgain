// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobModel.h
//! @brief     Defines class JobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#ifndef JOBMODEL_H
#define JOBMODEL_H

#include "SessionModel.h"
class JobQueueData;
class JobItem;
class MultiLayerItem;
class InstrumentItem;
class RealDataItem;
class SimulationOptionsItem;

class BA_CORE_API_ JobModel : public SessionModel
{
    Q_OBJECT

public:
    explicit JobModel(QObject *parent = 0);
    virtual ~JobModel();

    const JobItem *getJobItemForIndex(const QModelIndex &index) const;
    JobItem *getJobItemForIndex(const QModelIndex &index);

    JobItem *getJobItemForIdentifier(const QString &identifier);

    JobItem *addJob(const MultiLayerItem *multiLayerItem,
                    const InstrumentItem *instrumentItem,
                    const RealDataItem *realDataItem,
                    const SimulationOptionsItem *optionItem);

    void restore(JobItem *jobItem);

    bool hasUnfinishedJobs();

    void clear();

    void loadNonXMLData(const QString &projectDir);
    void saveNonXMLData(const QString &projectDir);

signals:
    void aboutToDeleteJobItem(JobItem *item);
    void focusRequest(JobItem *item);
    void globalProgress(int);

public slots:
    void onCancelAllJobs();
    void runJob(const QModelIndex &index);
    void cancelJob(const QModelIndex &index);
    void removeJob(const QModelIndex &index);

private:
    QString generateJobName();
    void restoreItem(SessionItem *item);
    JobQueueData *m_queue_data;
};

#endif // JOBMODEL_H
