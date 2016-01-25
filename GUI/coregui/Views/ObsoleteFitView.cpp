// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitView.cpp
//! @brief     Implements class FitView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "ObsoleteFitView.h"
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
#include "ItemIDFactory.h"

ObsoleteFitView::ObsoleteFitView(SampleModel *sModel, InstrumentModel *iModel, QWidget *parent)
    : QWidget(parent)
    , m_sampleModel(sModel)
    , m_instrumentModel(iModel)
{

    sampleTreeView = new QTreeView();
    instrumentTreeView = new QTreeView();
    fitTreeView = new QTreeView();

    //    SessionModel *testModel = new SessionModel("AAA");
    //    ParameterizedItem *item = testModel->insertNewItem(Constants::FitParameterType);
    //    ParameterizedItem *item2 = testModel->insertNewItem(Constants::FitParameterType);
    //    ParameterizedItem *item3 = testModel->insertNewItem(Constants::FitParameterType, testModel->indexOfItem(item));

    //ParameterizedItem *nullItemPtr = 0;

    //MultiLayerItem* rootOfSample = m_sampleModel->getMultiLayerItem();



    //QModelIndex rootIndexOfSample = m_sampleModel->indexOfItem(rootOfSample);

    //std::cout<<m_sampleModel->rowCount(m_sampleModel->indexOfItem(nullItemPtr)) << "\n";

    //m_sampleModel->itemForIndex(m_sampleModel->indexOfItem(nullItemPtr))->print();

    std::cout<<"============================================================================= \n";

    std::cout<<"Number of children of sample model is "<<m_sampleModel->rowCount(QModelIndex())<<"\n";

    m_fitParameterModel = new ObsoleteFitModel(3, ObsoleteFitModel::FitParameterModel);

    fitTreeView->setModel(m_fitParameterModel);

    //fitTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    fitTreeView->setDragEnabled(true);
    fitTreeView->setAcceptDrops(true);
    fitTreeView->setDropIndicatorShown(true);
    fitTreeView->setSelectionMode(QAbstractItemView::SingleSelection);


    //sampleTreeView->setModel(m_sampleModel);
    //FitModel* toyModel = new FitModel(3, FitModel::AcceptableFitModelNames.testModel);

    ParameterizedItem *newItem = m_fitParameterModel->insertNewItem(Constants::FitParameterType, QModelIndex());
    //newItem->registerProperty("Parameter", (double)0.0);
    //newItem->registerProperty("Ancestors", "scheiss");

    newItem = m_fitParameterModel->insertNewItem(Constants::FitParameterType, QModelIndex());
    //newItem->registerProperty("Parameter", (double)1.0);
    //newItem->registerProperty("Ancestors", "scheiss");

    newItem = m_fitParameterModel->insertNewItem(Constants::FitParameterType, QModelIndex());
    //newItem->registerProperty("Parameter", (double)2.0);
    //newItem->registerProperty("Ancestors", "scheiss");

    std::cout<<"============================================================================= \n";
    m_sampleParameterModel = new ObsoleteFitModel(2, ObsoleteFitModel::ProxySampleModel);

    //to be call extractSampleModel & extractInstrumentModel before calling sampleTreeView->setModel;
    extractSampleModel();
    extractInstrumentModel();

    sampleTreeView->setModel(m_sampleParameterModel);

    //sampleTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    sampleTreeView->setDragEnabled(true);
    sampleTreeView->setAcceptDrops(true);
    sampleTreeView->setDropIndicatorShown(true);
    sampleTreeView->setSelectionMode(QAbstractItemView::SingleSelection);
    //sampleTreeView->setModel(testModel);
    //=========================================================================================
    instrumentTreeView->setModel(m_instrumentModel);

    //=============================================================
    sampleSelectionModel = sampleTreeView->selectionModel();
    FitParameterSelectionModel = fitTreeView->selectionModel();

    connect(sampleSelectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
            this, SLOT(sampleSelectionChanged(const QItemSelection &, const QItemSelection &)));
    connect(FitParameterSelectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
            this, SLOT(fitParameterSelectionChanged(const QItemSelection &, const QItemSelection &)));
    //=============================================================

    //leftHalf = new QVBoxLayout;
    //rightHalf = new QVBoxLayout;
    wholeWindow = new QHBoxLayout(this);

    //leftHalf->setOrientation(Qt::Vertical);
    //leftHalf->addWidget(sampleTreeView);
    //leftHalf->addWidget(instrumentTreeView);

    //wholeWindow->addLayout(leftHalf);
    wholeWindow->addWidget(sampleTreeView);
    wholeWindow->addWidget(fitTreeView);

    //wholeWindow->setParent(this);
    this->show();


}


ParameterizedItem* ObsoleteFitView::extractSampleModel(const QModelIndex &parentIndex, ParameterizedItem *parentItem){

    Q_ASSERT(m_sampleModel);

    std::cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAA, FUUUUUUUUUUUUUUUUUU: "<< m_sampleModel->hasChildren()<<"\n";

    for (int i_row = 0; i_row < m_sampleModel->rowCount(parentIndex); ++i_row) {

        std::cout<<"in the "<<i_row<<" th row \n";

        QModelIndex itemIndex = m_sampleModel->index(i_row, 0, parentIndex);

        if (ParameterizedItem *item = m_sampleModel->itemForIndex(itemIndex)) {
            std::cout<< " Top item is " << item->modelType().toStdString()<<" and " << item->itemName().toStdString()<<"\n";
            item->print();

            //create new item
            QModelIndex parentIndex = m_sampleParameterModel->indexOfItem(parentItem);
            ParameterizedItem *standardItem = m_sampleParameterModel->insertNewItem(Constants::FitParameterType, parentIndex);
            standardItem->setItemName(item->itemName());
            standardItem->registerProperty("Parameter", QVariant());

            QList<QByteArray> propertyNameList = item->dynamicPropertyNames();

            for (int i = 0; i < propertyNameList.length(); ++i) {

                QString propertyName = QString(propertyNameList[i]);
                std::cout << "       property: "<< i << propertyName.toStdString() << " and subItems.size is: " << item->getSubItems().size()<<"\n";

                PropertyAttribute prop_attribute = item->getPropertyAttribute(propertyName);

                if (prop_attribute.getAppearance() & PropertyAttribute::HIDDEN)
                    continue;
                if (prop_attribute.getAppearance() & PropertyAttribute::DISABLED)
                    continue;

                QVariant propertyValue = item->property(propertyName.toUtf8().data());

                int type = GUIHelpers::getVariantType(propertyValue);
                if (type == QVariant::Double) {
                    std::cout << "       property: "<<propertyName.toStdString()<<" has value of "<< propertyValue.toDouble()<<"\n";
                    addPropertyToItem(standardItem, propertyName, "Parameter", propertyValue);

                } //end of property being a simple double number
                else if (item->getSubItems().contains(propertyName)) {
                    QMap<QString, ParameterizedItem *> subItems = item->getSubItems();
                    ParameterizedItem *subItem = subItems[propertyName];

                    std::cout << "           item: " << item->itemName().toStdString() << "has subItem:" << subItem->itemName().toStdString()<<"\n";

                    QModelIndex pIndex = m_sampleParameterModel->indexOfItem(standardItem);
                    ParameterizedItem *childStandardItem = m_sampleParameterModel->insertNewItem(Constants::FitParameterType, pIndex);
                    childStandardItem->setItemName(subItem->itemName());
                    childStandardItem->registerProperty("Parameter", QVariant());

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
                            std::cout << "            subItem has property: "<<childPropertyName.toStdString() <<" with value "<< childPropertyValue.toDouble()<<"\n";
                            isChildPropertyFound = true;
                            addPropertyToItem(childStandardItem, childPropertyName,"Parameter", childPropertyValue);
                        }
                    }
                    if (!isChildPropertyFound) {

                        int rowOfChild = standardItem->rowOfChild(childStandardItem);

                        QModelIndex parentIndex = m_sampleParameterModel->indexOfItem(standardItem);

                        m_sampleParameterModel->removeRow(rowOfChild, parentIndex);

                        //TO DO: what to do if child item does not have a double property. Delete it? How?
                        //insertRowIntoItem(standardItem, childStandardItem);
                    }
                } //end of property being a subItem

            }//end of Property name list

            if (parentItem == NULL) {
                parentItem = standardItem;
            } else {
                //insertRowIntoItem(parentItem, standardItem);
            }
            std::cout << "iteration called" << i_row<<"\n";
            extractSampleModel(itemIndex, standardItem);

        }//end of going through each child of itemIndexm

    }//end of iterating through children of itemIndex

    return parentItem;
}

/*void FitView::insertRowIntoItem(ParameterizedItem *parentItem, ParameterizedItem *childItem){

    //TODO extend session model, create own model type and use the session model method to insert child items.

    int row = parentItem->childItemCount();

    parentItem->insertChildItem(row, childItem);

    //m_fitParameterModel->insertNewItem(Constants::FitParameterType, m_fitParameterModel->indexOfItem(parentItem))

}*/

void ObsoleteFitView::addPropertyToItem(ParameterizedItem *parentItem, const QString &name, const QString &property_name, QVariant &value){

    QModelIndex parentIndex = m_sampleParameterModel->indexOfItem(parentItem);
    ParameterizedItem *newItem = m_sampleParameterModel->insertNewItem(Constants::FitParameterType,parentIndex);

    //operations directly on the data structure
    newItem->setItemName(name);
    newItem->registerProperty(property_name, value);

    QVariant check = newItem->getRegisteredProperty(property_name);

    std::cout<<property_name.toStdString()<<": Property can be accessed properly: "<<check.toString().toStdString()<<"\n";

    /*int row = parentItem->childItemCount();

    ParameterizedItem *childItem = new ParameterizedItem("FitModel");

    parentItem->insertChildItem(row, childItem);

    parentItem->childAt(row)->setItemName(name);
    parentItem->childAt(row)->registerProperty(property_name, value);*/

}

ParameterizedItem* ObsoleteFitView::extractInstrumentModel(){

    std::cout<<"Entered extractInstrumentModel \n";

    InstrumentItem *instrument
        = dynamic_cast<InstrumentItem *>(m_instrumentModel->getInstrumentItem());

    return iterateInstrumentItem(instrument);


}

ParameterizedItem* ObsoleteFitView::iterateInstrumentItem(InstrumentItem *instrument){

    std::cout<<"Entered iterateInstrumentItem \n";

    QModelIndex rootIndex = m_sampleParameterModel->indexOfItem(0);

    std::cout<<"    0";

    ParameterizedItem* item = m_sampleParameterModel->insertNewItem(Constants::FitParameterType, rootIndex);

    item->setItemName(instrument->itemName());

    std::cout<<"    1";

    BeamItem *beamItem = instrument->getBeamItem();
    if (beamItem) {
        //item = new ParameterizedItem(instrument->itemName());
        QVariant valueToPass;

        std::cout<<"    2";

        // intensity
        valueToPass = QVariant(beamItem->getIntensity());
        addPropertyToItem(item, BeamItem::P_INTENSITY, "Parameter", valueToPass);

        std::cout<<"    3";

        // wavelength, incident and azimuthal angle will be varied only if there is no distribution
        // assigned to them
        ParameterizedItem *beamWavelength = beamItem->getSubItems()[BeamItem::P_WAVELENGTH];

        Q_ASSERT(beamWavelength);
        ParameterizedItem *wavelengthDistribution
            = beamWavelength->getSubItems()[BeamDistributionItem::P_DISTRIBUTION];

        std::cout<<"    4";

        Q_ASSERT(wavelengthDistribution);
        if (wavelengthDistribution->modelType() == Constants::DistributionNoneType) {

            std::cout<<"    5";

            valueToPass = beamWavelength->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE);
            addPropertyToItem(
                item, BeamItem::P_WAVELENGTH, "Parameter", valueToPass);
        } else {
            //addDisabledProperty(item, BeamItem::P_WAVELENGTH);
        }

        ParameterizedItem *inclinationAngle
            = beamItem->getSubItems()[BeamItem::P_INCLINATION_ANGLE];

        std::cout<<"    6";

        Q_ASSERT(inclinationAngle);
        ParameterizedItem *inclinationDistribution
            = inclinationAngle->getSubItems()[BeamDistributionItem::P_DISTRIBUTION];

        std::cout<<"    7";

        Q_ASSERT(inclinationDistribution);
        if (inclinationDistribution->modelType() == Constants::DistributionNoneType) {

            std::cout<<"    8";

            valueToPass = inclinationAngle->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE);
            addPropertyToItem(
                item, BeamItem::P_INCLINATION_ANGLE, "Parameter",valueToPass);
        } else {
            //addDisabledProperty(item, BeamItem::P_INCLINATION_ANGLE);
        }

        ParameterizedItem *azimuthalAngle = beamItem->getSubItems()[BeamItem::P_AZIMUTHAL_ANGLE];

        std::cout<<"    9";

        Q_ASSERT(azimuthalAngle);
        ParameterizedItem *azimuthalDistribution
            = azimuthalAngle->getSubItems()[BeamDistributionItem::P_DISTRIBUTION];

        std::cout<<"    10";

        Q_ASSERT(azimuthalDistribution);
        if (azimuthalDistribution->modelType() == Constants::DistributionNoneType) {

            std::cout<<"    11";

            valueToPass = azimuthalAngle->getRegisteredProperty(BeamDistributionItem::P_CACHED_VALUE);
            addPropertyToItem(
                item, BeamItem::P_AZIMUTHAL_ANGLE, "Parameter", valueToPass);
        } else {
            //addDisabledProperty(item, BeamItem::P_AZIMUTHAL_ANGLE);
        }
    }

    return item;
}




void ObsoleteFitView::sampleSelectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection){

    Q_UNUSED(oldSelection);

    std::cout<<"Weeeeeeeeee sampleSelectionChangedSlot is properly connected to selectionChanged signal from sampleSelection Model \n";

    QModelIndexList listOfIndice =  newSelection.indexes();

    //if the newly selected sampleSelection is NOT empty
    if(listOfIndice.length() >0){

        ParameterizedItem* selectedItem = m_fitParameterModel->itemForIndex((listOfIndice.at(0)));
        QString itemName = selectedItem->itemName();
        QString itemGUID = selectedItem->getRegisteredProperty(ParameterizedItem::P_PORT).toString();

        std::cout<<"Looking for "<<itemName.toStdString()<<" and "<< itemGUID.toStdString()<<" \n";
        std::cout<<"Entering search"<<"\n";
        ParameterizedItem* correspondingItem = m_fitParameterModel->searchByNameGUID(itemName, itemGUID);\

        std::cout<<correspondingItem<<" is IT!\n";
        //std::cout<<NULL<<" is what NULL looks like\n";

        QString ID = ItemIDFactory::getID(correspondingItem);
        std::cout<<ID.toStdString()<<" is the ID \n";

        if(correspondingItem){

            QModelIndexList currentFitParameterModelSelection = FitParameterSelectionModel->selectedIndexes();
            ParameterizedItem* currentSelectedItem = NULL;

            if(currentFitParameterModelSelection.length() >0 ){
                currentSelectedItem = m_fitParameterModel->itemForIndex(currentFitParameterModelSelection.at(0));
                std::cout<<"    0 \n";
                // to check if current selection is already matching that of what we want
            }

            if(currentSelectedItem != correspondingItem){

                std::cout<<"    1 \n";
                QModelIndex correspondingIndex = m_fitParameterModel->indexOfItem(correspondingItem);
                std::cout<<"    2 \n";
                ParameterizedItem* parentItem = correspondingItem->parent();
                std::cout<<"    3 \n";
                QModelIndex parentIndex = m_fitParameterModel->indexOfItem(parentItem);
                std::cout<<"    4 \n";
                int rowOfItem = parentItem->rowOfChild(correspondingItem);
                std::cout<<"    5 \n";
                int columnsInRow = m_fitParameterModel->columnCount(correspondingIndex);
                std::cout<<"    6 \n";

                QModelIndex lastIndex = m_fitParameterModel->index(rowOfItem,columnsInRow-1, parentIndex);
                std::cout<<"    7 \n";
                QItemSelection correspondingSelection = QItemSelection(correspondingIndex,lastIndex);
                std::cout<<"    8 \n";

                FitParameterSelectionModel->select(correspondingSelection, QItemSelectionModel::ClearAndSelect);
                std::cout<<"    9 \n";
            }
            //std::cout<<"WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA pullin gmy hair outAAAAAAAAAAAAAAAAAAAAAAAA \n";
        }
        else{
            FitParameterSelectionModel->clearSelection();
        }
    }
    //ParameterizedItem* selectedItem = m_sampleParameterModel->itemForIndex((listOfIndice.first()));

}
void ObsoleteFitView::fitParameterSelectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection){

    Q_UNUSED(oldSelection);

    std::cout<<"Weeeeeeeeee sampleSelectionChangedSlot is properly connected to selectionChanged signal from sampleSelection Model \n";

    QModelIndexList listOfIndice =  newSelection.indexes();

    //if newly selected fitParameterSelection is not empty
    if(listOfIndice.length() > 0){
        ParameterizedItem* selectedItem = m_fitParameterModel->itemForIndex((listOfIndice.at(0)));
        QString itemName = selectedItem->itemName();
        //QString itemGUID = selectedItem->getRegisteredProperty(ParameterizedItem::P_ID).toString();

        try{
            QString item_predecessorGUID = selectedItem->getRegisteredProperty("Ancestors").toString();
            int stringSize = item_predecessorGUID.length();

            item_predecessorGUID.remove(0,stringSize - ItemIDFactory::IDSize());

            std::cout<<"Looking for "<<itemName.toStdString()<<" and "<< item_predecessorGUID.toStdString()<<" \n";
            std::cout<<"Entering search"<<"\n";

            ParameterizedItem* correspondingItem = m_sampleParameterModel->searchByNameGUID(itemName, item_predecessorGUID);\

            std::cout<<correspondingItem<<" is IT!\n";
            //std::cout<<NULL<<" is what NULL looks like\n";

            QString ID = ItemIDFactory::getID(correspondingItem);
            std::cout<<ID.toStdString()<<" is the ID \n";

            if(correspondingItem){

                QModelIndexList currentFitParameterModelSelection = sampleSelectionModel->selectedIndexes();
                ParameterizedItem* currentSelectedItem = NULL;

                if(currentFitParameterModelSelection.length() >0 ){
                    currentSelectedItem = m_sampleParameterModel->itemForIndex(currentFitParameterModelSelection.at(0));
                    std::cout<<"    0 \n";
                    // to check if current selection is already matching that of what we want
                }

                if(currentSelectedItem != correspondingItem){

                    std::cout<<"    1 \n";
                    QModelIndex correspondingIndex = m_sampleParameterModel->indexOfItem(correspondingItem);
                    std::cout<<"    2 \n";
                    ParameterizedItem* parentItem = correspondingItem->parent();
                    std::cout<<"    3 \n";
                    QModelIndex parentIndex = m_sampleParameterModel->indexOfItem(parentItem);
                    std::cout<<"    4 \n";
                    int rowOfItem = parentItem->rowOfChild(correspondingItem);
                    std::cout<<"    5 \n";
                    int columnsInRow = m_sampleParameterModel->columnCount(correspondingIndex);
                    std::cout<<"    6 \n";

                    QModelIndex lastIndex = m_sampleParameterModel->index(rowOfItem,columnsInRow-1, parentIndex);
                    std::cout<<"    7 \n";
                    QItemSelection correspondingSelection = QItemSelection(correspondingIndex,lastIndex);
                    std::cout<<"    8 \n";

                    sampleSelectionModel->select(correspondingSelection, QItemSelectionModel::ClearAndSelect);
                    std::cout<<"    9 \n";
                }
                //std::cout<<"WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA pullin gmy hair outAAAAAAAAAAAAAAAAAAAAAAAA \n";
            }
            else{
                sampleSelectionModel->clearSelection();
            }

        }

        catch(GUIHelpers::Error){
            sampleSelectionModel->clearSelection();
            return;

        }
    }

    /*ParameterizedItem* correspondingItem = m_fitParameterModel->searchByNameGUID(itemName, itemGUID);\

    std::cout<<correspondingItem<<" is IT!\n";
    //std::cout<<NULL<<" is what NULL looks like\n";

    QString ID = ItemIDFactory::getID(correspondingItem);
    std::cout<<ID.toStdString()<<" is the ID \n";

    QModelIndex correspondingIndex = m_fitParameterModel->indexOfItem(correspondingItem);
    if(correspondingItem){

        FitParameterSelectionModel->select(correspondingIndex, QItemSelectionModel::ClearAndSelect);
        //std::cout<<"WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA pullin gmy hair outAAAAAAAAAAAAAAAAAAAAAAAA \n";
    }
    else{
        FitParameterSelectionModel->clearSelection();
    }*/

}
/*
#include "FitView.h"
#include "FitParameterWidget.h"
#include "FitParameterWidgetOld.h"
#include "RunFitWidget.h"
#include "FitToolBar.h"
#include "qdebug.h"
#include "mainwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>


FitView::FitView(FitProxyModel *fitProxyModel, MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_fitProxyModel(fitProxyModel)
{

    m_FitParameterWidget = new FitParameterWidget();
    m_FitParameterWidgetOld = new FitParameterWidgetOld(m_fitProxyModel);
    m_runFitWidget = new RunFitWidget();

    m_tabWidget = new QTabWidget();
    m_tabWidget->insertTab(REAL_DATA, m_FitParameterWidget, tr("Real Data"));
    m_tabWidget->insertTab(FIT_PARAMETER, m_FitParameterWidgetOld, tr("Fit Parameters"));
    m_tabWidget->insertTab(RUN_FIT, m_runFitWidget, tr("Run Fit"));

    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));


    m_toolBar = new FitToolBar(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_tabWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}


void FitView::onChangeTabWidget(int index)
{

}
*/

/*
 * QStandardItem *ParameterModelBuilder::iterateInstrumentModel(InstrumentModel *instrumentModel)
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


void ParameterModelBuilder::addPropertyToParameterModel(QStandardItem *parentItem,
                                                        const QString &title,
                                                        const QString &property_name,
                                                        QVariant value,
                                                        ParameterizedItem *parameterizedItem)
*/
