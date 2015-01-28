// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterModelBuilder.cpp
//! @brief     Implements class ParameterModelBuilder
//!
//! @homepage  http://bornagainproject.org
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
#include "BeamItem.h"
#include "ItemLink.h"
#include "AngleProperty.h"
#include "GUIHelpers.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>


QStandardItemModel *ParameterModelBuilder::createParameterModel(SampleModel *sampleModel, InstrumentModel *instrumentModel)
{
    QStandardItemModel *result(0);
    result = new QStandardItemModel();
    result->setHorizontalHeaderItem( 0, new QStandardItem( "Property" ) );
    result->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );

    QStandardItem *sessionStandardItem = iterateSessionModel(sampleModel, QModelIndex(), 0);
    if(sessionStandardItem)
        result->appendRow(sessionStandardItem);

    QStandardItem *instrumentStandardItem = iterateInstrumentModel(instrumentModel);
    if(instrumentStandardItem)
        result->appendRow(instrumentStandardItem);

    return result;
}


QStandardItem *ParameterModelBuilder::iterateSessionModel(SampleModel *sampleModel, const QModelIndex &parentIndex, QStandardItem *parentItem)
{
    Q_ASSERT(sampleModel);

//    if(!parentIndex.isValid()) {
//        qDebug() << " ";
//        qDebug() << " ";
//        qDebug() << " ";
//        qDebug() << " ";
//        qDebug() << "Dumping model";
//    }


    for( int i_row = 0; i_row < sampleModel->rowCount( parentIndex ); ++i_row) {
        QModelIndex itemIndex = sampleModel->index( i_row, 0, parentIndex );

//        qDebug() << "   i_row" << i_row << parentIndex;


        if (ParameterizedItem *item = sampleModel->itemForIndex(itemIndex)){
            qDebug() << " item" << item->modelType() << item->itemName();
            item->print();

            QStandardItem *standardItem = new QStandardItem(item->itemName());

            QList<QByteArray> propertyNameList = item->dynamicPropertyNames();
            for (int i = 0; i < propertyNameList.length(); ++i) {
                QString propertyName = QString(propertyNameList[i]);
//                qDebug() << "       Items: i"<< i << propertyName << "subItems.size" << item->getSubItems().size();

                PropertyAttribute prop_attribute = item->getPropertyAttribute(propertyName);


                if(prop_attribute.getAppearance() & PropertyAttribute::HIDDEN) continue;
                if(prop_attribute.getAppearance() & PropertyAttribute::DISABLED) continue;

                //if(item->getPropertyAttribute(propertyName) & ParameterizedItem::HiddenProperty) continue;

                QVariant propertyValue = item->property(propertyName.toUtf8().data());

                int type = GUIHelpers::getVariantType(propertyValue);
                if (type == QVariant::Double) {
//                    qDebug() << "       Items: "<<propertyName << propertyValue.toDouble();
                    insertRowIntoItem(standardItem, propertyName, propertyValue, item);

                }
                else if(item->getSubItems().contains(propertyName)) {
                    QMap<QString, ParameterizedItem *> subItems = item->getSubItems();
                    ParameterizedItem *subItem = subItems[propertyName];

//                        qDebug() << "           Item: " << item->itemName() << "SubItem:" << subItem->itemName();

                        QStandardItem *childStandardItem = new QStandardItem(subItem->itemName());

                        QList<QByteArray> childPropertyList = subItem->dynamicPropertyNames();

                        bool isChildPropertyFound = false;

                        for (int j = 0; j < childPropertyList.length(); ++j) {
                            QString childPropertyName = QString(childPropertyList[j]);

                            PropertyAttribute prop_attribute = subItem->getPropertyAttribute(childPropertyName);
                            if(prop_attribute.getAppearance() & PropertyAttribute::HIDDEN) continue;
                            if(prop_attribute.getAppearance() & PropertyAttribute::DISABLED) continue;

                            QVariant childPropertyValue = subItem->property(childPropertyName.toUtf8().data());
                            int proValueType = GUIHelpers::getVariantType(childPropertyValue);
                            if (proValueType == QVariant::Double) {
                                //qDebug() << "Items: "<<prop_name << prop_value.toDouble();
                                isChildPropertyFound = true;
                                insertRowIntoItem(childStandardItem, childPropertyName, childPropertyValue, subItem);
                            }
                        }
                        if(isChildPropertyFound)
                        {
                            insertRowIntoItem(standardItem, childStandardItem);
                        }


                }


            }

            if(parentItem == NULL)
            {
                parentItem = standardItem;
            }
            else
            {
                insertRowIntoItem(parentItem, standardItem);
            }
            //qDebug() << "iteration called" << i_row;
            iterateSessionModel(sampleModel, itemIndex, standardItem);

        }

    }

    return parentItem;
}


QStandardItem *ParameterModelBuilder::iterateInstrumentModel(InstrumentModel *instrumentModel)
{
    QStandardItem *standardItem(0);

    InstrumentItem *instrument = instrumentModel->getInstrumentItem();
    if(instrument) {
        BeamItem *beamItem = instrument->getBeamItem();
        if(beamItem) {
            standardItem = new QStandardItem(instrument->itemName());
            insertRowIntoItem(standardItem, BeamItem::P_WAVELENGTH, beamItem->getRegisteredProperty(BeamItem::P_WAVELENGTH), beamItem);

            double v = beamItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).value<AngleProperty>().getValue();
            QVariant variant_inclination(v);
            insertRowIntoItem(standardItem, BeamItem::P_INCLINATION_ANGLE, variant_inclination, beamItem);

            v = beamItem->getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).value<AngleProperty>().getValue();
            insertRowIntoItem(standardItem, BeamItem::P_AZIMUTHAL_ANGLE, QVariant(v), beamItem);

        }
    }

    return standardItem;
}


void ParameterModelBuilder::insertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem)
{
    if(childValueItem == NULL)
    {
        childValueItem = new QStandardItem();
        childValueItem->setEditable(false);
        childTitleItem->setEditable(false);
    }

    parentItem->appendRow(QList<QStandardItem *>()  << childTitleItem << childValueItem);
}


void ParameterModelBuilder::insertRowIntoItem(QStandardItem *parentItem, QString title, QVariant value, ParameterizedItem *parameterizedItem)
{
    ItemLink itemLink(title, parameterizedItem);

    QVariant itemLinkData;
    itemLinkData.setValue(itemLink);

    QStandardItem *titleItem = new QStandardItem(title);
    titleItem->setEditable(false);
    QStandardItem *valueItem = new QStandardItem();

    valueItem->setData(itemLinkData, Qt::UserRole);
    valueItem->setData(value, Qt::EditRole);
    valueItem->setEditable(true);
    insertRowIntoItem(parentItem, titleItem, valueItem);
}

