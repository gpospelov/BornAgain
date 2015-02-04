// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobItem.h
//! @brief     Defines class NJobItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NJOBITEM_H
#define NJOBITEM_H

#include "ParameterizedItem.h"
class NIntensityDataItem;
class SampleModel;
class InstrumentModel;

class BA_CORE_API_ NJobItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_IDENTIFIER;
    static const QString P_BEGIN_TYPE;
    static const QString P_END_TYPE;
    static const QString P_COMMENTS;
    static const QString P_STATUS;
    static const QString P_PROGRESS;
    static const QString P_NTHREADS;
    static const QString P_RUN_POLICY;
    explicit NJobItem(ParameterizedItem *parent=0);
    ~NJobItem(){}

    NIntensityDataItem *getIntensityDataItem();

    SampleModel *getSampleModel();
    void setSampleModel(SampleModel *sampleModel);

    InstrumentModel *getInstrumentModel();
    void setInstrumentModel(InstrumentModel *instrumentModel);

    bool isIdle() const;
    bool isRunning() const;
    bool isCompleted() const;
    bool isCanceled() const;
    bool isFailed() const;

    QString getIdentifier() const;

private:
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;

};

#endif // NJOBITEM_H
