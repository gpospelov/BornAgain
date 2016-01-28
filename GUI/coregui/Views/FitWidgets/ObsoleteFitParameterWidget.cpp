// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidgetOld.cpp
//! @brief     Implements class FitParameterWidgetOld
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ObsoleteFitParameterWidget.h"
#include "ObsoleteFitParameterItem.h"
#include <QDebug>
#include <QVBoxLayout>



ObsoleteFitParameterWidget::ObsoleteFitParameterWidget(ObsoleteFitProxyModel *fitProxyModel, QWidget *parent)
    : QWidget(parent)
    , m_treeView(0)
    , m_fitProxyModel(fitProxyModel)
{

    QColor bgColor(255,255,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);


    initFitModel();

    m_fitProxyModel->setFitModel(m_fitModel);
    m_fitProxyModel->setHeaderData(0, Qt::Horizontal,"Title");

    /*if(m_fitModel)
    {
        ParameterizedItem *item1 = m_fitModel->insertNewItem(Constants::FitParameterType);
        item1->setItemName("par1");
        item1->setRegisteredProperty(FitParameterItem::P_MIN, 1.0);

        FitParameterItem *item2 = dynamic_cast<FitParameterItem *>(m_fitModel->insertNewItem(Constants::FitParameterType));
        item2->setItemName("par2");

//        ParameterizedItem *old_item = m_fitModel->itemForIndex(m_fitModel->index(0,0, QModelIndex()));
//        qDebug() << "FitModel: " << old_item->getRegisteredProperty(FitParameterItem::P_MIN);

//        FitParameterItem *fit_item = dynamic_cast<FitParameterItem *>(m_fitModel->itemForIndex(m_fitModel->index(1,0, QModelIndex())));
//        qDebug() << "FitModel: " << fit_item->getRegisteredProperty(FitParameterItem::P_MAX);



    }*/


    m_treeView = new QTreeView();
    m_treeView->setStyleSheet("QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item {border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: url(:/images/treeview-branch-open.png);}");


    //m_parameterModel = createParameterModel(m_fitModel);
    //connect(m_parameterModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onModelChanged(QModelIndex,QModelIndex)));



//    FitProxyModel *fitProxyModel = new FitProxyModel;
//    qDebug() << fitProxyModel;


    int height = this->height();
    m_treeView->setModel(m_fitProxyModel);
    m_treeView->setFixedHeight(height);
    m_treeView->setColumnWidth(0,170);
    m_treeView->expandAll();


    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_treeView);
    vlayout->addStretch();
    this->setLayout(vlayout);


//    QModelIndex idx = m_parameterModel->invisibleRootItem()->index();
//    for (int i=0; i<m_parameterModel->rowCount(); i++){
//    if (m_parameterModel->item(i,0)->hasChildren()){

//            m_treeView->setFirstColumnSpanned(0, m_parameterModel->item(i,0)->index(), true);
//            m_treeView->setFirstColumnSpanned(1, m_parameterModel->item(i,0)->index(), true);
//        }
//    }


}

QStandardItemModel *ObsoleteFitParameterWidget::createParameterModel(ObsoleteFitModel *fitModel)
{
    QStandardItemModel *result(0);
    result = new QStandardItemModel();
    result->setHorizontalHeaderItem( 0, new QStandardItem( "Property" ) );
    result->setHorizontalHeaderItem( 1, new QStandardItem( "Use" ) );
    result->setHorizontalHeaderItem( 2, new QStandardItem( "Value" ) );
    result->setHorizontalHeaderItem( 3, new QStandardItem( "Min" ) );
    result->setHorizontalHeaderItem( 4, new QStandardItem( "Max" ) );


    iterateSessionModel(fitModel, QModelIndex(), result);
//    if(standardItem)
//    {
//        result->appendRow(standardItem);
//    }

    return result;
}

QStandardItemModel *ObsoleteFitParameterWidget::iterateSessionModel(ObsoleteFitModel *fitModel, const QModelIndex &parentIndex, QStandardItemModel *parentItem)
{
    Q_ASSERT(fitModel);

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }


    for( int i_row = 0; i_row < fitModel->rowCount( parentIndex ); ++i_row) {
        QModelIndex itemIndex = fitModel->index( i_row, 0, parentIndex );



        if (ParameterizedItem *item = fitModel->itemForIndex(itemIndex)){


            qDebug() << "FitParameterWidgetOld::iterateSessionModel: " << item->itemName() << item->getRegisteredProperty(ObsoleteFitParameterItem::P_MIN)<<  item->getRegisteredProperty(ObsoleteFitParameterItem::P_MAX);

            insertRowIntoItem(parentItem, item->itemName(), item->getRegisteredProperty(ObsoleteFitParameterItem::P_VALUE), item->getRegisteredProperty(ObsoleteFitParameterItem::P_MIN), item->getRegisteredProperty(ObsoleteFitParameterItem::P_MAX), item->getRegisteredProperty(ObsoleteFitParameterItem::P_USE));

        }

    }

    return parentItem;
}

void ObsoleteFitParameterWidget::insertRowIntoItem(QStandardItemModel *parentItem, QString title, QVariant value, QVariant min, QVariant max, QVariant isUse)
{

    QStandardItem *titleItem = new QStandardItem(title);

    QStandardItem *useItem = new QStandardItem();
    useItem->setData(isUse, Qt::EditRole);
    useItem->setEditable(true);

    QStandardItem *valueItem = new QStandardItem();
    valueItem->setData(value, Qt::EditRole);
    valueItem->setEditable(true);

    QStandardItem *minItem = new QStandardItem();
    minItem->setData(min, Qt::EditRole);
    minItem->setEditable(true);

    QStandardItem *maxItem = new QStandardItem();
    maxItem->setData(max, Qt::EditRole);
    maxItem->setEditable(true);


    QStandardItem *subItem1 = new QStandardItem("this is the description 1 this is the description 1 this is the description 1");
    QStandardItem *subItem2 = new QStandardItem("this is the description 2 this is the description 2 this is the description 2");
    titleItem->appendRow(QList<QStandardItem *>() << subItem1 << new QStandardItem << new QStandardItem <<new QStandardItem <<new QStandardItem);
    titleItem->appendRow(subItem2);

    parentItem->appendRow(QList<QStandardItem *>()  << titleItem << useItem << valueItem << minItem << maxItem);

}

void ObsoleteFitParameterWidget::initFitModel()
{
    m_fitModel = new ObsoleteFitModel(2);

//    ParameterizedItem *item1 = m_fitModel->insertNewItem(Constants::FitParameterType);
//    item1->setItemName("Par1");
//    item1->setRegisteredProperty(FitParameterItem::P_USE, true);
//    item1->setRegisteredProperty(FitParameterItem::P_VALUE, 3.0);
//    item1->setRegisteredProperty(FitParameterItem::P_MIN, 1.0);
//    item1->setRegisteredProperty(FitParameterItem::P_MAX, 5.0);
//    //item1->setRegisteredProperty(FitParameterItem::P_NAME, tr("Par1"));

    ObsoleteFitParameterItem *item1 = dynamic_cast<ObsoleteFitParameterItem *>(m_fitModel->insertNewItem(Constants::FitParameterType));
    item1->setItemName("Par1");
    QStringList descList1;
    descList1 << "This is description 1" << "This is description 2" << "This is description 3";
    item1->setParNames(descList1);

    ObsoleteFitParameterItem *item2 = dynamic_cast<ObsoleteFitParameterItem *>(m_fitModel->insertNewItem(Constants::FitParameterType));
    item2->setItemName("Par2");
    QStringList descList2;
    descList2 << "This is description 1" << "This is description 2" << "This is description 3";
    item2->setParNames(descList2);

    ObsoleteFitParameterItem *item3 = dynamic_cast<ObsoleteFitParameterItem *>(m_fitModel->insertNewItem(Constants::FitParameterType));
    item3->setItemName("Par3");
    QStringList descList3;
    descList3 << "This is description 1" << "This is description 2" << "This is description 3";
    item3->setParNames(descList3);


    m_fitModel->save("fitmodel.xml");

    //ParameterizedItem *old_item = m_fitModel->itemForIndex(m_fitModel->index(0,0, QModelIndex()));
}
