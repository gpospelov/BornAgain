// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterModelBuilder.cpp
//! @brief     Implements class ParameterModelBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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

    for (int i_row = 0; i_row < sampleModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = sampleModel->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = sampleModel->itemForIndex(itemIndex)) {
            qDebug() << " item" << item->modelType() << item->itemName();
            item->print();

            QStandardItem *standardItem = new QStandardItem(item->itemName());

            QList<QByteArray> propertyNameList = item->dynamicPropertyNames();
            for (int i = 0; i < propertyNameList.length(); ++i) {
                QString propertyName = QString(propertyNameList[i]);
                //                qDebug() << "       Items: i"<< i << propertyName <<
                //                "subItems.size" << item->getSubItems().size();

                PropertyAttribute prop_attribute = item->getPropertyAttribute(propertyName);

                if (prop_attribute.getAppearance() & PropertyAttribute::HIDDEN)
                    continue;
                if (prop_attribute.getAppearance() & PropertyAttribute::DISABLED)
                    continue;

                // if(item->getPropertyAttribute(propertyName) & ParameterizedItem::HiddenProperty)
                // continue;

                QVariant propertyValue = item->property(propertyName.toUtf8().data());

                int type = GUIHelpers::getVariantType(propertyValue);
                if (type == QVariant::Double) {
                    //                    qDebug() << "       Items: "<<propertyName <<
                    //                    propertyValue.toDouble();
                    addPropertyToParameterModel(standardItem, propertyName, propertyName,
                                                propertyValue, item);

                } else if (item->getSubItems().contains(propertyName)) {
                    QMap<QString, ParameterizedItem *> subItems = item->getSubItems();
                    ParameterizedItem *subItem = subItems[propertyName];

                    //                        qDebug() << "           Item: " << item->itemName() <<
                    //                        "SubItem:" << subItem->itemName();

                    QStandardItem *childStandardItem = new QStandardItem(subItem->itemName());

                    QList<QByteArray> childPropertyList = subItem->dynamicPropertyNames();

                    bool isChildPropertyFound = false;

                    for (int j = 0; j < childPropertyList.length(); ++j) {
                        QString childPropertyName = QString(childPropertyList[j]);

                        PropertyAttribute prop_attribute
                            = subItem->getPropertyAttribute(childPropertyName);
                        if (prop_attribute.getAppearance() & PropertyAttribute::HIDDEN)
                            continue;
                        if (prop_attribute.getAppearance() & PropertyAttribute::DISABLED)
                            continue;

                        QVariant childPropertyValue
                            = subItem->property(childPropertyName.toUtf8().data());
                        int proValueType = GUIHelpers::getVariantType(childPropertyValue);
                        if (proValueType == QVariant::Double) {
                            // qDebug() << "Items: "<<prop_name << prop_value.toDouble();
                            isChildPropertyFound = true;
                            addPropertyToParameterModel(childStandardItem, childPropertyName,
                                                        childPropertyName, childPropertyValue,
                                                        subItem);
                        }
                    }
                    if (isChildPropertyFound) {
                        InsertRowIntoItem(standardItem, childStandardItem);
                    }
                }
            }

            if (parentItem == nullptr) {
                parentItem = standardItem;
            } else {
                InsertRowIntoItem(parentItem, standardItem);
            }
            // qDebug() << "iteration called" << i_row;
            iterateSessionModel(sampleModel, itemIndex, standardItem);
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

QStandardItem *ParameterModelBuilder::iterateInstrumentItem(InstrumentItem *instrument)
{
    QStandardItem *standardItem(0);
    BeamItem *beamItem = instrument->getBeamItem();
    if (beamItem) {
        standardItem = new QStandardItem(instrument->itemName());

        // intensity
        addPropertyToParameterModel(standardItem, BeamItem::P_INTENSITY, BeamItem::P_INTENSITY,
                                    QVariant(beamItem->getIntensity()), beamItem);

        // wavelength, incident and azimuthal angle will be varied only if there is no distribution
        // assigned to them
        ParameterizedItem *beamWavelength = beamItem->getSubItems()[BeamItem::P_WAVELENGTH];
        Q_ASSERT(beamWavelength);
        ParameterizedItem *wavelengthDistribution
            = beamWavelength->getSubItems()[BeamDistributionItem::P_DISTRIBUTION];
        Q_ASSERT(wavelengthDistribution);
        if (wavelengthDistribution->modelType() == Constants::DistributionNoneType) {
            addPropertyToParameterModel(
                standardItem, BeamItem::P_WAVELENGTH, BeamDistributionItem::P_CACHED_VALUE,
                beamWavelength->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE),
                beamWavelength);
        } else {
            addDisabledProperty(standardItem, BeamItem::P_WAVELENGTH);
        }

        ParameterizedItem *inclinationAngle
            = beamItem->getSubItems()[BeamItem::P_INCLINATION_ANGLE];
        Q_ASSERT(inclinationAngle);
        ParameterizedItem *inclinationDistribution
            = inclinationAngle->getSubItems()[BeamDistributionItem::P_DISTRIBUTION];
        Q_ASSERT(inclinationDistribution);
        if (inclinationDistribution->modelType() == Constants::DistributionNoneType) {
            addPropertyToParameterModel(
                standardItem, BeamItem::P_INCLINATION_ANGLE, BeamDistributionItem::P_CACHED_VALUE,
                inclinationAngle->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE),
                inclinationAngle);
        } else {
            addDisabledProperty(standardItem, BeamItem::P_INCLINATION_ANGLE);
        }

        ParameterizedItem *azimuthalAngle = beamItem->getSubItems()[BeamItem::P_AZIMUTHAL_ANGLE];
        Q_ASSERT(azimuthalAngle);
        ParameterizedItem *azimuthalDistribution
            = azimuthalAngle->getSubItems()[BeamDistributionItem::P_DISTRIBUTION];
        Q_ASSERT(azimuthalDistribution);
        if (azimuthalDistribution->modelType() == Constants::DistributionNoneType) {
            addPropertyToParameterModel(
                standardItem, BeamItem::P_AZIMUTHAL_ANGLE, BeamDistributionItem::P_CACHED_VALUE,
                azimuthalAngle->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE),
                azimuthalAngle);
        } else {
            addDisabledProperty(standardItem, BeamItem::P_AZIMUTHAL_ANGLE);
        }
    }

    return standardItem;
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

//! adds property of ParameterizedItem to the QStandardItem of ParameterTree
//! title - the name of the property as it will be shown by QTreeView
//! property_name - the name of the property to add (normally coincide with 'title')
//! value - QVariant representing property_value
void ParameterModelBuilder::addPropertyToParameterModel(QStandardItem *parentItem,
                                                        const QString &title,
                                                        const QString &property_name,
                                                        QVariant value,
                                                        ParameterizedItem *parameterizedItem)
{
    ItemLink itemLink(property_name, parameterizedItem);

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
