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

#include "ParameterizedItem.h"
class IntensityDataItem;
class SampleModel;
class InstrumentModel;
class GISASSimulation;
class MultiLayerItem;
class InstrumentItem;

class BA_CORE_API_ JobItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_IDENTIFIER;
    static const QString P_SAMPLE_NAME;
    static const QString P_INSTRUMENT_NAME;
    static const QString P_STATUS;
    static const QString P_BEGIN_TIME;
    static const QString P_END_TIME;
    static const QString P_COMMENTS;
    static const QString P_PROGRESS;
    static const QString P_NTHREADS;
    static const QString P_RUN_POLICY;
    explicit JobItem(ParameterizedItem *parent=0);
    virtual ~JobItem();

    QString getIdentifier() const;
    void setIdentifier(const QString &identifier);

    IntensityDataItem *getIntensityDataItem();

    QString getStatus() const;
    void setStatus(const QString &status);

    bool isIdle() const;
    bool isRunning() const;
    bool isCompleted() const;
    bool isCanceled() const;
    bool isFailed() const;

    void setBeginTime(const QString &begin_time);

    void setEndTime(const QString &end_time);

    QString getComments() const;
    void setComments(const QString &comments);

    int getProgress() const;
    void setProgress(int progress);

    int getNumberOfThreads() const;
    void setNumberOfThreads(int number_of_threads);

    void setRunPolicy(const QString &run_policy);

    static QMap<QString, QString> getRunPolicies() { return m_run_policies; }

    bool runImmediately() const;
    bool runInBackground() const;

    MultiLayerItem *getMultiLayerItem(bool from_backup = false);

    InstrumentItem *getInstrumentItem(bool from_backup = false);

    void setResults(const GISASSimulation *simulation);

private:
    static QMap<QString, QString> m_run_policies; // run policy, policy description
};

#endif // NJOBITEM_H
