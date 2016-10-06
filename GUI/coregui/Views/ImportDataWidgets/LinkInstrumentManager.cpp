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
#include "LinkInstrumentItem.h"
#include "AxesItems.h"
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>


namespace {
const QString undefinedInstrumentName = "Undefined";
}

LinkInstrumentManager::InstrumentInfo::InstrumentInfo()
    : m_name(undefinedInstrumentName)
    , m_instrument(0)
{}


LinkInstrumentManager::LinkInstrumentManager(QObject *parent)
    : QObject(parent)
    , m_instrumentModel(0)
    , m_realDataModel(0)
{
}

void LinkInstrumentManager::setModels(InstrumentModel *instrumentModel,
                                      RealDataModel *realDataModel)
{
    setInstrumentModel(instrumentModel);
    setRealDataModel(realDataModel);
    updateInstrumentMap();
    updateRealDataMap();
    updateLinks();
}

void LinkInstrumentManager::setOnInstrumentPropertyChange(SessionItem *instrument, const QString &property)
{
    Q_ASSERT(instrument);
    qDebug() << "LinkInstrumentManager::setOnInstrumentPropertyChange" << instrument->itemName() << property;
    if(property == SessionItem::P_NAME || property == InstrumentItem::P_IDENTIFIER) {
        updateInstrumentMap();
    }
}

void LinkInstrumentManager::setOnRealDataPropertyChange(SessionItem *dataItem, const QString &property)
{
    qDebug() << "AAAAA setOnRealDataPropertyChange" << dataItem << property;
    if(property == RealDataItem::P_INSTRUMENT_ID) {
        qDebug() << "AAAAA 2.1";
        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(dataItem);
        QString identifier = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        realDataItem->linkToInstrument(getInstrument(identifier));
        qDebug() << "AAAAA 2.2";
    }
}

void LinkInstrumentManager::onInstrumentChildChange(SessionItem *instrument, SessionItem *child)
{
    qDebug() << "onInstrumentChildChange" << instrument->modelType() << child->modelType() << child->itemName();
    if(child->itemName() == BasicAxisItem::P_NBINS)
        onInstrumentBinningChange(instrument);
}

//! Updates map of instruments on insert/remove instrument.

void LinkInstrumentManager::onInstrumentRowsChange(const QModelIndex &parent, int, int)
{
    // valid parent means not an instrument (which is top level item) but something below
    if(parent.isValid())
        return;

    updateInstrumentMap();
    updateLinks();
}

//! Updates map of data on insert/remove event.

void LinkInstrumentManager::onRealDataRowsChange(const QModelIndex &parent, int, int)
{
    // valid parent means not a data (which is top level item) but something below
    if(parent.isValid())
        return;

    updateRealDataMap();
    updateLinks();
}


//! Returns name of the instrument from identifier

QString LinkInstrumentManager::instrumentNameFromIdentifier(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return m_instrumentVec[i].m_name;

    throw GUIHelpers::Error("LinkInstrumentManager::instrumentNameFromIdentifier() -> Error. "
                            "Unknown instrument identifier.");
}

//! Returns instrument's identifier from its name

//QString LinkInstrumentManager::instrumentIdentifierFromName(const QString &name)
//{
//    for(int i=0; i<m_instrumentVec.size(); ++i)
//        if(m_instrumentVec[i].m_name == name)
//            return m_instrumentVec[i].m_identifier;

//    return QString();
//}

InstrumentItem *LinkInstrumentManager::getInstrument(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return m_instrumentVec[i].m_instrument;

    return nullptr;
}

QStringList LinkInstrumentManager::instrumentNames() const
{
    QStringList result;
    for(int i=0; i<m_instrumentVec.size(); ++i)
        result.append(m_instrumentVec[i].m_name);
    return result;
}

int LinkInstrumentManager::instrumentComboIndex(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return i;

    return -1; // no such identifier exists
}

QString LinkInstrumentManager::instrumentIdentifier(int comboIndex)
{
    Q_ASSERT(comboIndex >= 0 && comboIndex < m_instrumentVec.size());
    return m_instrumentVec[comboIndex].m_identifier;
}

//bool LinkInstrumentManager::canLinkDataToInstrument(RealDataItem *realDataItem,
//                                                    InstrumentItem *instrumentItem)
//{
//}

bool LinkInstrumentManager::canLinkDataToInstrument(const RealDataItem *realDataItem,
                                                    const QString &identifier)
{
    InstrumentItem *instrumentItem = getInstrument(identifier);

    // linking to null instrument is possible, it means unlinking from currently linked
    if(instrumentItem == nullptr)
        return true;

    QString message;
    if(ImportDataAssistant::hasSameDimensions(instrumentItem, realDataItem, message))
       return true;

    bool canLink(false);

    QMessageBox msgBox;
    msgBox.setText("The shape of data and detector differs.");

    QString informative;
    informative.append(message);
    informative.append("\n\nDo you want to modify instrument so it matches shape of real data?\n\n");
    msgBox.setInformativeText(informative);

    QPushButton *modifyInstrumentButton = msgBox.addButton("Yes, please modify instrument",
                                                           QMessageBox::YesRole);
    QPushButton *cancelButton = msgBox.addButton("No, leave as it is",
                                                 QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton() == modifyInstrumentButton) {
        canLink = true;
        ImportDataAssistant::setInstrumentShapeToData(instrumentItem, realDataItem);
    } else if (msgBox.clickedButton() == cancelButton) {
        canLink = false;
    }

    return canLink;
}

void LinkInstrumentManager::updateLinks()
{
    foreach(SessionItem *item, m_realDataModel->topItems(Constants::RealDataType)) {
        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(item);
        Q_ASSERT(realDataItem);

        QString identifier = realDataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        InstrumentItem *instrumentItem = getInstrument(identifier);

        if(!instrumentItem) {
            realDataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
        } else {
            realDataItem->linkToInstrument(instrumentItem);
        }

    }
}


void LinkInstrumentManager::updateInstrumentMap()
{
    m_instrumentVec.clear();
    m_instrumentVec.append(InstrumentInfo()); // undefined instrument
    foreach(SessionItem *item, m_instrumentModel->topItems(Constants::InstrumentType)) {
        item->mapper()->unsubscribe(this);

        item->mapper()->setOnPropertyChange(
                    [this, item](const QString &name)
        {
            setOnInstrumentPropertyChange(item, name);
        }, this);

        item->mapper()->setOnAnyChildChange(
            [this, item] (SessionItem* child)
        {
            onInstrumentChildChange(item, child);
        }, this);


        InstrumentInfo info;
        info.m_name = item->itemName();
        info.m_identifier = item->getItemValue(InstrumentItem::P_IDENTIFIER).toString();
        info.m_instrument = dynamic_cast<InstrumentItem *>(item);
        m_instrumentVec.append(info);
    }

    emit instrumentMapUpdated();
}

void LinkInstrumentManager::updateRealDataMap()
{
    foreach(SessionItem *dataItem, m_realDataModel->topItems(Constants::RealDataType)) {
        dataItem->mapper()->unsubscribe(this);

        dataItem->mapper()->setOnPropertyChange(
                    [this, dataItem](const QString &name)
        {
            setOnRealDataPropertyChange(dataItem, name);
        }, this);

    }

}

//! Runs through all RealDataItem and break the link, if instrument binning doesn't match the data.

void LinkInstrumentManager::onInstrumentBinningChange(SessionItem *changedInstrument)
{
    Q_ASSERT(changedInstrument);

    foreach(SessionItem *item, m_realDataModel->topItems(Constants::RealDataType)) {
        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(item);

        QString identifier = realDataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        InstrumentItem *instrumentItem = getInstrument(identifier);
        if(instrumentItem == changedInstrument) {
            QString message;
            if(!ImportDataAssistant::hasSameDimensions(instrumentItem, realDataItem, message)) {
                qDebug() << "Breaking the link " << identifier;
                realDataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
            }
        }
    }
}

//! Sets connections for instrument model.

void LinkInstrumentManager::setInstrumentModel(InstrumentModel *model)
{
    if (m_instrumentModel) {
        disconnect(m_instrumentModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(onInstrumentRowsChange(QModelIndex,int,int)));
        disconnect(m_instrumentModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(onInstrumentRowsChange(QModelIndex, int, int)));
    }

    m_instrumentModel = model;

    if (m_instrumentModel) {
        connect(m_instrumentModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(onInstrumentRowsChange(QModelIndex, int, int)));
        connect(m_instrumentModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(onInstrumentRowsChange(QModelIndex, int, int)));
    }
}

//! Sets connections for real data model.

void LinkInstrumentManager::setRealDataModel(RealDataModel *model)
{
    if (m_realDataModel) {
        disconnect(m_realDataModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(onRealDataRowsChange(QModelIndex, int, int)));
        disconnect(m_realDataModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(onRealDataRowsChange(QModelIndex, int, int)));
        disconnect(m_realDataModel, SIGNAL(modelLoaded()),
                   this, SLOT(updateLinks()));
    }

    m_realDataModel = model;

    if (m_realDataModel) {
        connect(m_realDataModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(onRealDataRowsChange(QModelIndex, int, int)));
        connect(m_realDataModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(onRealDataRowsChange(QModelIndex, int, int)));
        connect(m_realDataModel, SIGNAL(modelLoaded()),
                   this, SLOT(updateLinks()));
    }
}
