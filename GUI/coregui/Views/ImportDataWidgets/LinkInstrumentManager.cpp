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
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>

namespace {
const QString undefinedInstrumentName = "Undefined";
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
    updateLinks();
}


void LinkInstrumentManager::setOnInstrumentPropertyChange(SessionItem *instrument, const QString &property)
{
    Q_ASSERT(instrument);
    qDebug() << "LinkInstrumentManager::setOnInstrumentPropertyChange" << instrument->itemName() << property;
    if(property == SessionItem::P_NAME) {        
        updateLinks();
    }
}

void LinkInstrumentManager::setOnRealDataPropertyChange(SessionItem *dataItem, const QString &property)
{
    qDebug() << "AAAAA" << dataItem << property;
    if(property == RealDataItem::P_INSTRUMENT_COMBO) {
        QString currentIdentifier = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        ComboProperty combo = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_COMBO).value<ComboProperty>();

        qDebug() << " AAAA";
        qDebug() << " AAAA";
        qDebug() << " AAAA 0.1" << combo.getValue();

        QString instrName = combo.getValue();

        QString identifier = instrumentIdentifierFromName(instrName);

        if(identifier == currentIdentifier)
            return;

        qDebug() << " AAAA 0.2";

        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(dataItem);
        Q_ASSERT(realDataItem);


        qDebug() << " AAAAAAA" << combo.getValue() << combo.getCachedValue() << currentIdentifier << identifier;

        if(canLinkDataToInstrument(realDataItem, getInstrument(identifier))) {
            qDebug() << "AAAAA 1.1";
            dataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, identifier);
            dataItem->setItemValue(RealDataItem::P_INSTRUMENT_NAME, instrName);
            qDebug() << "AAAAA 1.2";
//            realDataItem->linkToInstrument(getInstrument(identifier));
        } else {
            QString prevName = instrumentNameFromIdentifier(currentIdentifier);
            qDebug() << "AAAAA 1.3" << prevName;
//            dataItem->setItemValue(RealDataItem::P_INSTRUMENT_NAME, prevName);
            qDebug() << "AAAAA 1.4";
            combo.setValue(prevName);
//            realDataItem->mapper()->setActive(false);

            dataItem->setItemValue(RealDataItem::P_INSTRUMENT_COMBO, combo.getVariant());
            dataItem->getItem(RealDataItem::P_INSTRUMENT_COMBO)->emitDataChanged(Qt::DisplayRole);
//            realDataItem->mapper()->setActive(true);

            qDebug() << "AAAAA 1.5";
        }
    }

    else if(property == RealDataItem::P_INSTRUMENT_ID) {
        qDebug() << "AAAAA 2.1";
        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(dataItem);
        QString identifier = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        realDataItem->linkToInstrument(getInstrument(identifier));
        qDebug() << "AAAAA 2.2";
    }

}

void LinkInstrumentManager::setInstrumentModel(InstrumentModel *model)
{
    if (m_instrumentModel) {
        disconnect(m_instrumentModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(updateLinks()));
        disconnect(m_instrumentModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(updateLinks()));
    }

    m_instrumentModel = model;

    if (m_instrumentModel) {
        connect(m_instrumentModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(updateLinks()));
        connect(m_instrumentModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(updateLinks()));
    }

}

void LinkInstrumentManager::setRealDataModel(RealDataModel *model)
{
    if (m_realDataModel) {
        disconnect(m_realDataModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(updateRealDataMap()));
        disconnect(m_realDataModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(updateRealDataMap()));
    }

    m_realDataModel = model;

    if (m_realDataModel) {
        connect(m_realDataModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                   this, SLOT(updateRealDataMap()));
        connect(m_realDataModel, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                   this, SLOT(updateRealDataMap()));
    }
}

//! Returns name of the instrument from identifier

QString LinkInstrumentManager::instrumentNameFromIdentifier(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return m_instrumentVec[i].m_name;

    return undefinedInstrumentName;
}

//! Returns instrument's identifier from its name

QString LinkInstrumentManager::instrumentIdentifierFromName(const QString &name)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_name == name)
            return m_instrumentVec[i].m_identifier;

    return QString();
}

InstrumentItem *LinkInstrumentManager::getInstrument(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return m_instrumentVec[i].m_instrument;

    return nullptr;
}

QStringList LinkInstrumentManager::instrumentNames() const
{
    QStringList result = QStringList() << undefinedInstrumentName;
    for(int i=0; i<m_instrumentVec.size(); ++i)
        result.append(m_instrumentVec[i].m_name);
    return result;
}

bool LinkInstrumentManager::canLinkDataToInstrument(RealDataItem *realDataItem,
                                                    InstrumentItem *instrumentItem)
{
    // linking to null instrument is possible, it means unlinking from previous one
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
        // connect
        ImportDataAssistant::setInstrumentShapeToData(instrumentItem, realDataItem);
    } else if (msgBox.clickedButton() == cancelButton) {
        canLink = false;
    }

    return canLink;
}

void LinkInstrumentManager::updateLinks()
{
    updateInstrumentMap();
    updateRealDataMap();
}


void LinkInstrumentManager::updateInstrumentMap()
{
    Q_ASSERT(m_realDataModel);

//    m_instrumentInfo.clear();
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
//        m_instrumentInfo[item] = info;
        m_instrumentVec.append(info);
    }
}

void LinkInstrumentManager::updateRealDataMap()
{
    foreach(SessionItem *dataItem, m_realDataModel->topItems(Constants::RealDataType)) {
        dataItem->mapper()->unsubscribe(this);

        QString identifier = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        QString instrName = instrumentNameFromIdentifier(identifier);
        if(instrName == undefinedInstrumentName) {
            dataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
        }

        ComboProperty combo = ComboProperty() << instrumentNames();
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

