// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h
//! @brief     Defines class LinkInstrumentManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef LINKINSTRUMENTMANAGER_H
#define LINKINSTRUMENTMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QMap>
#include <QVector>

class InstrumentModel;
class RealDataModel;
class SessionItem;
class InstrumentItem;
class IntensityDataItem;

//! The LinkInstrumentManager class provides communication between InstrumentModel and
//! RealDataModel. Particularly, it notifies RealDataItem about changes in linked instruments.

class BA_CORE_API_ LinkInstrumentManager : public QObject {
    Q_OBJECT

public:
    class InstrumentInfo
    {
    public:
        InstrumentInfo() : m_instrument(0){}
        QString m_identifier;
        QString m_name;
        InstrumentItem *m_instrument;
    };

    explicit LinkInstrumentManager(QObject *parent =  0);

    void setModels(InstrumentModel *instrumentModel, RealDataModel *realDataModel);

public slots:
    void setOnInstrumentPropertyChange(SessionItem *instrument, const QString &property);
    void setOnRealDataPropertyChange(SessionItem *dataItem, const QString &property);

private slots:
    void updateInstrumentMap();

private:
    void setInstrumentModel(InstrumentModel *model);
    void setRealDataModel(RealDataModel *model);
    InstrumentInfo& getInstrumentInfo(SessionItem *item);
    QString instrumentNameFromIdentifier(const QString &identifier);
    InstrumentItem *getInstrument(const QString &identifier);

    InstrumentModel *m_instrumentModel;
    RealDataModel *m_realDataModel;
    QStringList m_instrumentNames;
    QMap<SessionItem *, InstrumentInfo> m_instrumentInfo;
    QVector<InstrumentInfo> m_instrumentVec;
};

#endif
