// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobItem.h
//! @brief     Defines class JobItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBITEM_H
#define JOBITEM_H

#include "SessionItem.h"
class IntensityDataItem;
class SampleModel;
class InstrumentModel;
class GISASSimulation;
class MultiLayerItem;
class InstrumentItem;

class BA_CORE_API_ JobItem : public SessionItem
{

public:
    static const QString P_IDENTIFIER;
    static const QString P_SAMPLE_NAME;
    static const QString P_INSTRUMENT_NAME;
    static const QString P_WITH_FITTING;
    static const QString P_STATUS;
    static const QString P_BEGIN_TIME;
    static const QString P_END_TIME;
    static const QString P_COMMENTS;
    static const QString P_PROGRESS;
    static const QString P_NTHREADS;
    static const QString P_RUN_POLICY;
    static const QString T_SAMPLE;
    static const QString T_INSTRUMENT;
    static const QString T_OUTPUT;
    static const QString T_REALDATA;
    static const QString T_PARAMETER_TREE;
    static const QString T_SIMULATION_OPTIONS;
    explicit JobItem();
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

    MultiLayerItem *getMultiLayerItem();

    InstrumentItem *getInstrumentItem();

    void setResults(const GISASSimulation *simulation);

private:
    static QMap<QString, QString> m_run_policies; // run policy, policy description
};

#endif // NJOBITEM_H
