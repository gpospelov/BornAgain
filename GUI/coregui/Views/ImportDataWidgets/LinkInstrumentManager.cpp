// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.cpp
//! @brief     Implements class LinkInstrumentManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "LinkInstrumentManager.h"
#include "InstrumentModel.h"
#include "RealDataModel.h"
#include "InstrumentItem.h"
#include "RealDataItem.h"
#include "ComboProperty.h"
#include "SessionItem.h"
#include "GUIHelpers.h"
#include "JobItemHelper.h"
#include "ImportDataAssistant.h"
#include "IntensityDataItem.h"
#include "DomainObjectBuilder.h"
#include "Instrument.h"
#include <QDebug>

namespace {
const QString undefinedInstrument = "Undefined";
}

LinkInstrumentManager::LinkInstrumentManager(QObject *parent)
    : QObject(parent)
    , m_instrumentModel(0)
    , m_realDataModel(0)
{

}

void LinkInstrumentManager::setModels(InstrumentModel *instrumentModel, RealDataModel *realDataModel)
{
    setInstrumentModel(instrumentModel);
    setRealDataModel(realDataModel);
    updateInstrumentMap();
}

void LinkInstrumentManager::setOnInstrumentPropertyChange(SessionItem *instrument, const QString &property)
{
    Q_ASSERT(instrument);
    qDebug() << "LinkInstrumentManager::setOnInstrumentPropertyChange" << instrument->itemName() << property;
    if(property == SessionItem::P_NAME) {
//        InstrumentInfo& info = getInstrumentInfo(instrument);
//        info.m_name = instrument->itemName();
    }
}

void LinkInstrumentManager::setOnRealDataPropertyChange(SessionItem *dataItem, const QString &property)
{
    if(property == RealDataItem::P_INSTRUMENT_COMBO) {
        ComboProperty combo = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_COMBO).value<ComboProperty>();
        QString instrName = combo.getValue();

        dataItem->setItemValue(RealDataItem::P_INSTRUMENT_NAME, instrName);

        int index = m_instrumentNames.indexOf(instrName);
        QString identifier;
        if(index >= 0)
            identifier = m_instrumentVec[index].m_identifier;
        dataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, identifier);

        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(dataItem);
        Q_ASSERT(realDataItem);

        IntensityDataItem *intensityDataItem = realDataItem->intensityDataItem();

        updateDataAxes(intensityDataItem, getInstrument(identifier));

    }

}

void LinkInstrumentManager::setInstrumentModel(InstrumentModel *model)
{
    if (m_instrumentModel) {
        disconnect(m_instrumentModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(updateInstrumentMap()));
        disconnect(m_instrumentModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(updateInstrumentMap()));
    }

    m_instrumentModel = model;

    if (m_instrumentModel) {
        connect(m_instrumentModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(updateInstrumentMap()));
        connect(m_instrumentModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(updateInstrumentMap()));
    }

}

void LinkInstrumentManager::setRealDataModel(RealDataModel *model)
{
    if (m_realDataModel) {
        disconnect(m_realDataModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(updateInstrumentMap()));
        disconnect(m_realDataModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(updateInstrumentMap()));
    }

    m_realDataModel = model;

    if (m_realDataModel) {
        connect(m_realDataModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(updateInstrumentMap()));
        connect(m_realDataModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(updateInstrumentMap()));
    }
}

LinkInstrumentManager::InstrumentInfo &LinkInstrumentManager::getInstrumentInfo(SessionItem *item)
{
    auto it = m_instrumentInfo.find(item);
    if(it == m_instrumentInfo.end())
        throw GUIHelpers::Error("LinkInstrumentManager::getInstrumentInfo() -> Error. No such "
                                "instrument");

    return it.value();
}

//! Returns name of the instrument from identifier

QString LinkInstrumentManager::instrumentNameFromIdentifier(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return m_instrumentVec[i].m_name;

    return undefinedInstrument;
}

InstrumentItem *LinkInstrumentManager::getInstrument(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return m_instrumentVec[i].m_instrument;

    return nullptr;
}

void LinkInstrumentManager::updateDataAxes(IntensityDataItem *intensityDataItem,
                                           const InstrumentItem *instrumentItem)
{
    if(instrumentItem == 0) {
        ComboProperty combo;
        combo << Constants::UnitsNbins;
        intensityDataItem->setItemValue(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
        intensityDataItem->getItem(IntensityDataItem::P_AXES_UNITS)->setVisible(true);
        intensityDataItem->setXaxisTitle("X [nbins]");
        intensityDataItem->setYaxisTitle("Y [nbins]");
        intensityDataItem->setOutputData(ImportDataAssistant::createSimlifiedOutputData(*intensityDataItem->getOutputData()));

    }

    else {
        OutputData<double> *newData = JobItemHelper::createDefaultDetectorMap(instrumentItem);
        newData->setRawDataVector(intensityDataItem->getOutputData()->getRawDataVector());

        intensityDataItem->setOutputData(newData);
        intensityDataItem->setAxesRangeToData();


//        ComboProperty combo;
//        combo << Constants::UnitsNbins;
//        intensityItem->setItemValue(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
//        intensityItem->getItem(IntensityDataItem::P_AXES_UNITS)->setVisible(true);


    }


}

void LinkInstrumentManager::updateInstrumentMap()
{
    Q_ASSERT(m_realDataModel);

    m_instrumentNames.clear();
    m_instrumentInfo.clear();
    m_instrumentVec.clear();
    foreach(SessionItem *item, m_instrumentModel->topItems(Constants::InstrumentType)) {
        item->mapper()->unsubscribe(this);
        item->mapper()->setOnPropertyChange(
                    [this, item](const QString &name)
        {
            setOnInstrumentPropertyChange(item, name);
        }, this);

        InstrumentInfo info;
        info.m_name = item->itemName();
        info.m_identifier = item->getItemValue(InstrumentItem::P_IDENTIFIER).toString();
        info.m_instrument = dynamic_cast<InstrumentItem *>(item);
        m_instrumentInfo[item] = info;
        m_instrumentNames.push_back(item->itemName());
        m_instrumentVec.append(info);
    }

    qDebug() << "XXXX LinkInstrumentManager::updateInstrumentMap()" << m_instrumentNames;

    foreach(SessionItem *dataItem, m_realDataModel->topItems(Constants::RealDataType)) {
        dataItem->mapper()->unsubscribe(this);

//        ComboProperty combo = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_COMBO).value<ComboProperty>();

        QString identifier = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        QString instrName = instrumentNameFromIdentifier(identifier);
        if(instrName == undefinedInstrument) {
            dataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
        }

        ComboProperty combo;
        combo << undefinedInstrument << m_instrumentNames;
        combo.setValue(instrName);

        dataItem->setItemValue(RealDataItem::P_INSTRUMENT_COMBO, combo.getVariant());
        dataItem->setItemValue(RealDataItem::P_INSTRUMENT_NAME, instrName);

        dataItem->mapper()->setOnPropertyChange(
                    [this, dataItem](const QString &name)
        {
            setOnRealDataPropertyChange(dataItem, name);
        }, this);

    }
}

