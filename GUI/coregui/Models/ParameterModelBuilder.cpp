// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterModelBuilder.cpp
//! @brief     Implements class ParameterModelBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterModelBuilder.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "InstrumentItem.h"
#include "JobItem.h"
#include "JobModel.h"
#include "BeamItem.h"
#include "BeamDistributionItem.h"
#include "BeamWavelengthItem.h"
#include "MultiLayerItem.h"
#include "InstrumentItem.h"
#include "ItemLink.h"
#include "AngleProperty.h"
#include "GUIHelpers.h"
#include "DistributionItem.h"
#include "GroupItem.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>

QStandardItemModel *ParameterModelBuilder::createParameterModel(JobModel *jobModel,
                                                                JobItem *jobItem)
{
    QStandardItemModel *result(0);

    result = new QStandardItemModel();
    result->setHorizontalHeaderItem(0, new QStandardItem("Property"));
    result->setHorizontalHeaderItem(1, new QStandardItem("Value"));

    QStandardItem *sessionStandardItem
        = iterateSessionModel(jobModel, jobModel->indexOfItem(jobItem->getMultiLayerItem()), 0);
    if (sessionStandardItem)
        result->appendRow(sessionStandardItem);

    QStandardItem *instrumentStandardItem = iterateInstrumentItem(jobItem->getInstrumentItem());
    if (instrumentStandardItem)
        result->appendRow(instrumentStandardItem);

    return result;
}

QStandardItem *ParameterModelBuilder::iterateSessionModel(SessionModel *sampleModel,
                                                          const QModelIndex &parentIndex,
                                                          QStandardItem *parentItem)
{
    Q_ASSERT(sampleModel);
    if (!parentItem) {
        parentItem = new QStandardItem(sampleModel->itemForIndex(parentIndex)->itemName());
    }

    for (int i_row = 0; i_row < sampleModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = sampleModel->index(i_row, 0, parentIndex);

        if (SessionItem *item = sampleModel->itemForIndex(itemIndex)) {
            if (!item->isEnabled() || !item->isVisible())
                continue;
            if (item->modelType() == Constants::PropertyType) {
                // insert double property
                if (GUIHelpers::getVariantType(item->value()) == QVariant::Double) {
                    QString name = item->itemName();
                    addPropertyToParameterModel(parentItem, name, name,
                                                          item->value(), item);
                }
            } else if (item->modelType() == Constants::GroupItemType) {
                if (GroupItem *gItem = dynamic_cast<GroupItem*>(item)) {
                    QString groupItemname = gItem->group()->getCurrentItem()->itemName();
                    if (gItem->group()->isFixed()) {
                        groupItemname = gItem->itemName();
                    }
                    QStandardItem *newGroupItem = new QStandardItem(groupItemname);
                    InsertRowIntoItem(parentItem, newGroupItem);
                    iterateSessionModel(sampleModel, item->parent()->getGroupItem(item->itemName())->index(), newGroupItem);
                }

            } else {
                QStandardItem *newItem = new QStandardItem(item->itemName());
                InsertRowIntoItem(parentItem, newItem);
                iterateSessionModel(sampleModel, itemIndex, newItem);
            }
        }
    }

    return parentItem;
}

QStandardItem *ParameterModelBuilder::iterateInstrumentModel(InstrumentModel *instrumentModel)
{
    InstrumentItem *instrument
        = dynamic_cast<InstrumentItem *>(instrumentModel->getInstrumentItem());
    return iterateInstrumentItem(instrument);
}

QStandardItem *ParameterModelBuilder::iterateInstrumentItem(InstrumentItem *)
{
    // TODO take care of instrument parameters, do it somewhat less cumbersome
    return nullptr;
}

void ParameterModelBuilder::InsertRowIntoItem(QStandardItem *parentItem,
                                              QStandardItem *childTitleItem,
                                              QStandardItem *childValueItem)
{
    if (childValueItem == nullptr) {
        childValueItem = new QStandardItem();
        childValueItem->setEditable(false);
        childTitleItem->setEditable(false);
    }

    parentItem->appendRow(QList<QStandardItem *>() << childTitleItem << childValueItem);
}

//! adds property of SessionItem to the QStandardItem of ParameterTree
//! title - the name of the property as it will be shown by QTreeView
//! property_name - the name of the property to add (normally coincide with 'title')
//! value - QVariant representing property_value
void ParameterModelBuilder::addPropertyToParameterModel(QStandardItem *parentItem,
                                                        const QString &title,
                                                        const QString &property_name,
                                                        QVariant value,
                                                        SessionItem *parameterizedItem)
{
    ItemLink itemLink(property_name, parameterizedItem->parent());

    QVariant itemLinkData;
    itemLinkData.setValue(itemLink);

    QStandardItem *titleItem = new QStandardItem(title);
    titleItem->setEditable(false);
    QStandardItem *valueItem = new QStandardItem();

    valueItem->setData(itemLinkData, Qt::UserRole);
    valueItem->setData(value, Qt::EditRole);
    valueItem->setEditable(true);
    InsertRowIntoItem(parentItem, titleItem, valueItem);
}

void ParameterModelBuilder::addDisabledProperty(QStandardItem *parentItem, const QString &title)
{
    QStandardItem *titleItem = new QStandardItem(title);
    titleItem->setEditable(false);
    QStandardItem *valueItem = new QStandardItem("disabled");
    valueItem->setEditable(false);

    QFont font("Arial", 8);
    font.setItalic(true);
    valueItem->setData(font, Qt::FontRole);
    valueItem->setData("Editing disabled because of the distribution attached to this item.",
                       Qt::ToolTipRole);

    InsertRowIntoItem(parentItem, titleItem, valueItem);
}
