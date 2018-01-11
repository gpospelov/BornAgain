// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h
//! @brief     Defines class LinkInstrumentManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef LINKINSTRUMENTMANAGER_H
#define LINKINSTRUMENTMANAGER_H

#include "WinDllMacros.h"
#include <QObject>
#include <QVector>
#include <QList>
#include <QStringList>

class InstrumentModel;
class RealDataModel;
class SessionItem;
class GISASInstrumentItem;
class RealDataItem;
class SessionModel;

//! The LinkInstrumentManager class provides communication between InstrumentModel and
//! RealDataModel. Particularly, it notifies RealDataItem about changes in linked instruments
//! to adjust axes of IntensityDataItem.

class BA_CORE_API_ LinkInstrumentManager : public QObject {
    Q_OBJECT

public:
    class InstrumentInfo
    {
    public:
        InstrumentInfo();
        QString m_identifier;
        QString m_name;
        GISASInstrumentItem *m_instrument;
    };

    explicit LinkInstrumentManager(QObject *parent =  0);

    void setModels(InstrumentModel *instrumentModel, RealDataModel *realDataModel);

    GISASInstrumentItem *getInstrument(const QString &identifier);
    QStringList instrumentNames() const;
    int instrumentComboIndex(const QString &identifier);
    QString instrumentIdentifier(int comboIndex);
    bool canLinkDataToInstrument(const RealDataItem *realDataItem, const QString &identifier);

    QList<RealDataItem *> linkedItems(GISASInstrumentItem *instrumentItem);

signals:
    void instrumentMapUpdated();

private slots:
    void setOnInstrumentPropertyChange(SessionItem *instrument, const QString &property);
    void setOnRealDataPropertyChange(SessionItem *dataItem, const QString &property);
    void onInstrumentChildChange(GISASInstrumentItem *instrument, SessionItem *child);
    void onInstrumentRowsChange(const QModelIndex & parent, int, int);
    void onRealDataRowsChange(const QModelIndex & parent, int, int);

    void updateLinks();
    void updateInstrumentMap();
    void updateRealDataMap();
    void onInstrumentBinningChange(GISASInstrumentItem *changedInstrument);
    void onInstrumentLayoutChange(GISASInstrumentItem *changedInstrument);

private:
    void setInstrumentModel(InstrumentModel *model);
    void setRealDataModel(RealDataModel *model);

    InstrumentModel *m_instrumentModel;
    RealDataModel *m_realDataModel;
    QVector<InstrumentInfo> m_instrumentVec;
};

#endif // LINKINSTRUMENTMANAGER_H
