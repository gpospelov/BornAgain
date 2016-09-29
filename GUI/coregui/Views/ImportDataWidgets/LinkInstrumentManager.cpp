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
#include <QDebug>

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

void LinkInstrumentManager::updateInstrumentMap()
{
    Q_ASSERT(m_realDataModel);

    m_instrumentNames.clear();
    foreach(SessionItem *item, m_instrumentModel->topItems(Constants::InstrumentType)) {
        m_instrumentNames.push_back(item->itemName());
    }

    qDebug() << "XXXX LinkInstrumentManager::updateInstrumentMap()" << m_instrumentNames;

    foreach(SessionItem *dataItem, m_realDataModel->topItems(Constants::RealDataType)) {
//        ComboProperty combo = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_COMBO).value<ComboProperty>();
        ComboProperty combo;
        combo << "Undefined" << m_instrumentNames;
        dataItem->setItemValue(RealDataItem::P_INSTRUMENT_COMBO, combo.getVariant());
    }
}

