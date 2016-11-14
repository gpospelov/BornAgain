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
#include "ImportDataAssistant.h"
#include "AxesItems.h"
#include "DetectorItems.h"
#include "MaskItems.h"
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

//! Sets models and builds initial links.

void LinkInstrumentManager::setModels(InstrumentModel *instrumentModel,
                                      RealDataModel *realDataModel)
{
    setInstrumentModel(instrumentModel);
    setRealDataModel(realDataModel);
    updateInstrumentMap();
    updateRealDataMap();
    updateLinks();
}

//! Returns InstrumentItem for given identifier.

InstrumentItem *LinkInstrumentManager::getInstrument(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return m_instrumentVec[i].m_instrument;

    return nullptr;
}

//! Returns list of instrument names including artificial name "Undefined".

QStringList LinkInstrumentManager::instrumentNames() const
{
    QStringList result;
    for(int i=0; i<m_instrumentVec.size(); ++i)
        result.append(m_instrumentVec[i].m_name);
    return result;
}

//! Returns combo index for instrument selector from given identifier.

int LinkInstrumentManager::instrumentComboIndex(const QString &identifier)
{
    for(int i=0; i<m_instrumentVec.size(); ++i)
        if(m_instrumentVec[i].m_identifier == identifier)
            return i;

    return -1; // no such identifier exists
}

//! Returns instrument identifier from given index in combo instrument selector.

QString LinkInstrumentManager::instrumentIdentifier(int comboIndex)
{
    Q_ASSERT(comboIndex >= 0 && comboIndex < m_instrumentVec.size());
    return m_instrumentVec[comboIndex].m_identifier;
}

//! Returns true if RealDataItem can be linked to the instrument (same number of bins).
//! Also offers dialog to adjust instrument to match shape of real data.

bool LinkInstrumentManager::canLinkDataToInstrument(const RealDataItem *realDataItem,
                                                    const QString &identifier)
{
    InstrumentItem *instrumentItem = getInstrument(identifier);

    // linking to null instrument is possible, it means unlinking from currently linked
    if(instrumentItem == nullptr)
        return true;

    // FIXME temporary hack to get rid from Instrument's own masks and ROI
    DetectorItem *detectorItem = instrumentItem->detectorItem();
    if(SessionItem *maskContainer = detectorItem->maskContainerItem()) {
        SessionItem *item = detectorItem->takeRow(detectorItem->rowOfChild(maskContainer));
        delete item;
    }

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

//! Calls rebuild of instrument map if the name or identifier of the instrument have changed.

void LinkInstrumentManager::setOnInstrumentPropertyChange(SessionItem *instrument,
                                                          const QString &property)
{
    Q_ASSERT(instrument);
    if(property == SessionItem::P_NAME || property == InstrumentItem::P_IDENTIFIER) {
        updateInstrumentMap();
    }
}

//! Link or re-link RealDataItem to the instrument on identifier change.

void LinkInstrumentManager::setOnRealDataPropertyChange(SessionItem *dataItem,
                                                        const QString &property)
{
    if(property == RealDataItem::P_INSTRUMENT_ID) {
        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(dataItem);
        QString identifier = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        realDataItem->linkToInstrument(getInstrument(identifier));
    }
}

//! Perform actions on instrument children change.

void LinkInstrumentManager::onInstrumentChildChange(InstrumentItem *instrument, SessionItem *child)
{
    if(child == nullptr)
        return;

    qDebug() << "SSS 1.1" << child->modelType() << child->itemName();
    qDebug() << "SSS 1.1" << child->parent()->modelType() << child->parent()->itemName();


    if(child->itemName() == BasicAxisItem::P_NBINS ||
       child->parent()->itemName() == DetectorItem::P_DETECTOR) {
        onInstrumentBinningChange(instrument);
    } else {
        onInstrumentLayoutChange(instrument);
    }
}

//! Updates map of instruments on insert/remove InstrumentItem event.

void LinkInstrumentManager::onInstrumentRowsChange(const QModelIndex &parent, int, int)
{
    // valid parent means not an instrument (which is top level item) but something below
    if(parent.isValid())
        return;

    updateInstrumentMap();
    updateLinks();
}

//! Updates map of data on insert/remove RealDataItem event.

void LinkInstrumentManager::onRealDataRowsChange(const QModelIndex &parent, int, int)
{
    // valid parent means not a data (which is top level item) but something below
    if(parent.isValid())
        return;

    updateRealDataMap();
    updateLinks();
}

//! Runs through all RealDataItem and check all links.

void LinkInstrumentManager::updateLinks()
{
    foreach(SessionItem *item, m_realDataModel->topItems(Constants::RealDataType)) {
        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(item);
        Q_ASSERT(realDataItem);

        QString identifier = realDataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        InstrumentItem *instrumentItem = getInstrument(identifier);

        if(!instrumentItem) {
            // if no instrument with P_INSTRUMENT_ID exists, break the link
            realDataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
        } else {
            // refresh the link to update axes
            realDataItem->linkToInstrument(instrumentItem);
        }
    }
}

//! Builds the map of existing instruments, their names, identifiers and sets up callbacks.

void LinkInstrumentManager::updateInstrumentMap()
{
    m_instrumentVec.clear();
    m_instrumentVec.append(InstrumentInfo()); // undefined instrument
    foreach(SessionItem *item, m_instrumentModel->topItems(Constants::InstrumentType)) {
        InstrumentItem *instrumentItem = dynamic_cast<InstrumentItem *>(item);
        instrumentItem->mapper()->unsubscribe(this);

        instrumentItem->mapper()->setOnPropertyChange(
                    [this, item](const QString &name)
        {
            setOnInstrumentPropertyChange(item, name);
        }, this);

        instrumentItem->mapper()->setOnAnyChildChange(
            [this, instrumentItem] (SessionItem* child)
        {
            onInstrumentChildChange(instrumentItem, child);
        }, this);

        InstrumentInfo info;
        info.m_name = item->itemName();
        info.m_identifier = item->getItemValue(InstrumentItem::P_IDENTIFIER).toString();
        info.m_instrument = instrumentItem;
        m_instrumentVec.append(info);
    }

    emit instrumentMapUpdated();
}

//! Sets callbacks for all RealDataItem.

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

void LinkInstrumentManager::onInstrumentBinningChange(InstrumentItem *changedInstrument)
{
    foreach(RealDataItem *realDataItem, linkedItems(changedInstrument)) {
        if(!ImportDataAssistant::hasSameDimensions(changedInstrument, realDataItem)) {
            qDebug() << "Breaking the link ";
            realDataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
        }
    }
}

//! Runs through all RealDataItem and refresh linking to match possible change in detector
//! axes definition.

void LinkInstrumentManager::onInstrumentLayoutChange(InstrumentItem *changedInstrument)
{
    foreach(RealDataItem *realDataItem, linkedItems(changedInstrument)) {
        qDebug() << "Changing layout";
        realDataItem->linkToInstrument(changedInstrument);
    }
}

//! Returns list of RealDataItem's linked to given instrument.

QList<RealDataItem *> LinkInstrumentManager::linkedItems(InstrumentItem *instrumentItem)
{
    QList<RealDataItem *> result;
    foreach(SessionItem *item, m_realDataModel->topItems(Constants::RealDataType)) {
        RealDataItem *realDataItem = dynamic_cast<RealDataItem *>(item);

        QString linkedIdentifier
            = realDataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        QString instrumentIdentifier
            = instrumentItem->getItemValue(InstrumentItem::P_IDENTIFIER).toString();

        if(linkedIdentifier == instrumentIdentifier)
            result.append(realDataItem);
    }
    return result;
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
