#include "QuickSimulationHelper.h"
#include "Simulation.h"
#include "Instrument.h"
#include "MultiLayer.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "DomainObjectBuilder.h"
#include "ParameterizedItem.h"
#include "BeamItem.h"
#include "ItemLink.h"
#include <QDebug>
#include <iostream>
#include <QStandardItem>
#include <QStandardItemModel>


Simulation *QuickSimulationHelper::getSimulation(SampleModel *sampleModel, const QString &sample_name, InstrumentModel *instrumentModel, const QString &instrument_name)
{
    qDebug() << "QuickSimulationHelper::getSimulation() " << sample_name << instrument_name;

    Simulation *result = new Simulation;

    MultiLayer *multilayer = getMultiLayer(sampleModel, sample_name);
    Q_ASSERT(multilayer);

    Instrument *instrument = getInstrument(instrumentModel, instrument_name);
    Q_ASSERT(instrument);

    result->setSample(*multilayer);
    result->setInstrument(*instrument);

    delete multilayer;
    delete instrument;

    return result;
}


Instrument *QuickSimulationHelper::getInstrument(InstrumentModel *instrumentModel, const QString &instrument_name)
{
    qDebug() << "QuickSimulationHelper::getInstrument()";
    Q_ASSERT(instrumentModel);
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < instrumentModel->rowCount( parentIndex); ++i_row) {
        QModelIndex itemIndex = instrumentModel->index( i_row, 0, parentIndex );

        if (ParameterizedItem *item = instrumentModel->itemForIndex(itemIndex)){
            qDebug() << "      MainWindow::updateInstruments()" << item->itemName() << item->modelType();
            if(item->modelType() == Constants::InstrumentType && item->itemName() == instrument_name) {
                DomainObjectBuilder builder;
                Instrument *instrument = builder.buildInstrument(*item);
                //std::cout << *instrument << std::endl;
                return instrument;
            }
        }
    }

    return 0;
}


MultiLayer *QuickSimulationHelper::getMultiLayer(SampleModel *sampleModel, const QString &sample_name)
{
    qDebug() << "QuickSimulationHelper::getMultiLayer()";
    Q_ASSERT(sampleModel);
    QModelIndex parentIndex;
    for( int i_row = 0; i_row < sampleModel->rowCount( parentIndex); ++i_row) {
        QModelIndex itemIndex = sampleModel->index( i_row, 0, parentIndex );

        if (ParameterizedItem *item = sampleModel->itemForIndex(itemIndex)){
            if(item->modelType() == Constants::MultiLayerType && item->itemName() == sample_name) {
                DomainObjectBuilder builder;
                MultiLayer *multilayer = builder.buildMultiLayer(*item);
                //multilayer->printSampleTree();
                return multilayer;
            }
        }
    }
    return 0;
}

QStandardItemModel *QuickSimulationHelper::createParameterModel(SampleModel *sampleModel, InstrumentModel *instrumentModel)
{
    QStandardItemModel *result(0);
    result = new QStandardItemModel();
    result->setHorizontalHeaderItem( 0, new QStandardItem( "Property" ) );
    result->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );

    //Gennady
    //    QStandardItem *multiLayerItem = new QStandardItem(m_sample_name);
    //    QModelIndex multiLayerIndex = getMultiLayerIndex(m_sample_name);
    //    result->setItem(0, iterateSessionModel(multiLayerIndex, multiLayerItem));

    //Mahadi
    QStandardItem *sessionStandardItem = iterateSessionModel(sampleModel, QModelIndex(), 0);
    //result->setItem(0, sessionStandardItem);
    if(sessionStandardItem)
    {
        result->appendRow(sessionStandardItem);
    }



    QStandardItem *instrumentStandardItem = iterateInstrumentModel(instrumentModel);
    if(instrumentStandardItem)
    {
        result->appendRow(instrumentStandardItem);
    }




    return result;
}

QStandardItem *QuickSimulationHelper::iterateSessionModel(SampleModel *sampleModel, const QModelIndex &parentIndex, QStandardItem *parentItem)
{
    Q_ASSERT(sampleModel);

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }


    for( int i_row = 0; i_row < sampleModel->rowCount( parentIndex ); ++i_row) {
        QModelIndex itemIndex = sampleModel->index( i_row, 0, parentIndex );



        if (ParameterizedItem *item = sampleModel->itemForIndex(itemIndex)){

            QStandardItem *standardItem = new QStandardItem(item->itemName());

            QList<QByteArray> propertyNameList = item->dynamicPropertyNames();
            for (int i = 0; i < propertyNameList.length(); ++i) {
                QString propertyName = QString(propertyNameList[i]);

                PropertyAttribute prop_attribute = item->getPropertyAttribute(propertyName);\


                //Mahadi: limit test. have to remove later
                //prop_attribute.setLimits(AttLimits::limited(0.0, 1000.0));
                //item->setPropertyAttribute(propertyName, prop_attribute);
                //AttLimits limits = prop_attribute.getLimits();
                //qDebug() << "ModelTuningWidget::iterateSessionModel(): limits: " << limits.hasLowerLimit() << limits.hasUpperLimit();
                //end of limit test

                if(prop_attribute.getAppearance() & PropertyAttribute::HiddenProperty) continue;

                //if(item->getPropertyAttribute(propertyName) & ParameterizedItem::HiddenProperty) continue;

                QVariant propertyValue = item->property(propertyName.toUtf8().data());

                int type = propertyValue.type();
                if (type == QVariant::Double) {
                    //qDebug() << "Items: "<<prop_name << prop_value.toDouble();
                    insertRowIntoItem(standardItem, propertyName, propertyValue, item);

                }

                if(item->getSubItems().contains(propertyName)) {
                    QMap<QString, ParameterizedItem *> subItems = item->getSubItems();

                    foreach (ParameterizedItem *subItem, subItems) {

                        //qDebug() << "Item: " << item->itemName() << "SubItem:" << subItem->itemName();

                        QStandardItem *childStandardItem = new QStandardItem(subItem->itemName());

                        QList<QByteArray> childPropertyList = subItem->dynamicPropertyNames();

                        bool isChildPropertyFound = false;

                        for (int j = 0; j < childPropertyList.length(); ++j) {
                            QString childPropertyName = QString(childPropertyList[j]);

                            PropertyAttribute prop_attribute = item->getPropertyAttribute(childPropertyName);
                            if(prop_attribute.getAppearance() & PropertyAttribute::HiddenProperty) continue;

                            QVariant childPropertyValue = subItem->property(childPropertyName.toUtf8().data());
                            int proValueType = childPropertyValue.type();
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

QStandardItem *QuickSimulationHelper::iterateInstrumentModel(InstrumentModel *instrumentModel)
{
    QStandardItem *standardItem;

    QModelIndex itemIndex = instrumentModel->index(0,0,QModelIndex());
    ParameterizedItem *instrument = instrumentModel->itemForIndex(itemIndex);

    ParameterizedItem *beamParameterizedItem;

    BeamItem *beamItem(0);
    foreach(ParameterizedItem *item, instrument->childItems()) {
        item->print();
        if(item->modelType() == Constants::BeamType) {
            beamItem = dynamic_cast<BeamItem *>(item);
            beamParameterizedItem = item;
            break;
        }
    }

    if(beamItem)
    {
        standardItem = new QStandardItem(instrument->itemName());

        insertRowIntoItem(standardItem, BeamItem::P_WAVELENGTH, beamItem->getRegisteredProperty(BeamItem::P_WAVELENGTH), beamParameterizedItem);

    }


    return standardItem;
}

void QuickSimulationHelper::insertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem)
{
    if(childValueItem == NULL)
    {
        childValueItem = new QStandardItem();
        childValueItem->setEditable(false);
    }

    parentItem->appendRow(QList<QStandardItem *>()  << childTitleItem << childValueItem);

}

void QuickSimulationHelper::insertRowIntoItem(QStandardItem *parentItem, QString title, QVariant value, ParameterizedItem *parameterizedItem)
{
    ItemLink itemLink(title, parameterizedItem);
    QVariant itemLinkData;
    itemLinkData.setValue(itemLink);

    QStandardItem *titleItem = new QStandardItem(title);
    QStandardItem *valueItem = new QStandardItem();

    valueItem->setData(itemLinkData, Qt::UserRole);
    valueItem->setData(value, Qt::EditRole);
    valueItem->setEditable(true);
    insertRowIntoItem(parentItem, titleItem, valueItem);

}
