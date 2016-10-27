// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItem.h
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
class GISASSimulation;
class MultiLayerItem;
class InstrumentItem;
class SimulationOptionsItem;
class FitSuiteItem;
class ParameterContainerItem;
class FitParameterContainerItem;
class RealDataItem;

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
    static const QString P_DURATION;
    static const QString P_COMMENTS;
    static const QString P_PROGRESS;
    static const QString T_SAMPLE;
    static const QString T_INSTRUMENT;
    static const QString T_OUTPUT;
    static const QString T_REALDATA;
    static const QString T_PARAMETER_TREE;
    static const QString T_SIMULATION_OPTIONS;
    static const QString T_FIT_SUITE;
    explicit JobItem();
    virtual ~JobItem();

    QString getIdentifier() const;
    void setIdentifier(const QString &identifier);

    IntensityDataItem *intensityDataItem();

    QString getStatus() const;
    void setStatus(const QString &status);

    bool isIdle() const;
    bool isRunning() const;
    bool isCompleted() const;
    bool isCanceled() const;
    bool isFailed() const;
    bool isValidForFitting();

    void setBeginTime(const QString &begin_time);

    void setEndTime(const QString &end_time);

    void setDuration(int duration);

    QString getComments() const;
    void setComments(const QString &comments);

    int getProgress() const;
    void setProgress(int progress);

    int getNumberOfThreads() const;

    void setRunPolicy(const QString &run_policy);

    bool runImmediately() const;
    bool runInBackground() const;

    MultiLayerItem *multiLayerItem();

    InstrumentItem *instrumentItem();

    SimulationOptionsItem *getSimulationOptionsItem();

    void setResults(const GISASSimulation *simulation);

    FitSuiteItem *fitSuiteItem();
    ParameterContainerItem *parameterContainerItem();
    FitParameterContainerItem *fitParameterContainerItem();
    RealDataItem *realDataItem();

private:
    void updateIntensityDataFileName();
    const SimulationOptionsItem *getSimulationOptionsItem() const;
};

#endif // JOBITEM_H
