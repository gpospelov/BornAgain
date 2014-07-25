#include "SampleTuningWidget.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "PropertyAttribute.h"
#include "SampleTuningDelegate.h"
#include "ItemLink.h"
#include <QItemSelectionModel>
#include <QDebug>

SampleTuningWidget::SampleTuningWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent)
    : QWidget(parent)
    , m_parameterModel(0)
    , m_treeView(0)
    , m_delegate(new SampleTuningDelegate(1))
    , m_sampleModel(sampleModel)
    , m_instrumentModel(instrumentModel)
{

    //generate Tree View
    m_treeView = new QTreeView(this);
    //treeView->setModel(model);
    //m_itemModel = getItemModelFromSessionModel();
    //treeView->setModel(getTestItemModel());

    m_treeView->setStyleSheet("QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item {border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: url(:/images/treeview-branch-open.png);}");
    //treeView->setStyleSheet("QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item {background: cyan;}QTreeView::branch:has-siblings:adjoins-item {background: red;}QTreeView::branch:!has-children:!has-siblings:adjoins-item {background: blue;}QTreeView::branch:closed:has-children:has-siblings {background: pink;}QTreeView::branch:has-children:!has-siblings:closed {background: gray;}QTreeView::branch:open:has-children:has-siblings {background: magenta;}QTreeView::branch:open:has-children:!has-siblings {background: green;}");

    m_treeView->setFixedWidth(380);
    m_treeView->setFixedHeight(600);
    m_treeView->setColumnWidth(0,220);
    m_treeView->expandAll();

    //QItemSelectionModel *selectionModel = treeView->selectionModel();
    //m_delegate = new TestViewDelegate(this, treeView->selectionModel());
    //treeView->setItemDelegateForColumn(1, m_delegate);



    m_treeView->setItemDelegate(m_delegate);


    //generate Table View
    /*m_tableWidget = new QTableWidget(5, 2,this);
    m_tableWidget->setItemDelegate(new TestViewDelegate(1));
    m_tableWidget->setHorizontalHeaderLabels(
            QStringList() << tr("Name") << tr("Value"));

    m_tableWidget->setFixedWidth(350);
    m_tableWidget->setColumnWidth(1,200);
    m_tableWidget->setColumnWidth(0,100);

    for (int row = 0; row < 5; ++row) {

        QTableWidgetItem *item0 = new QTableWidgetItem(tr("test"));
        m_tableWidget->setItem(row, 0, item0);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        double itemValue = (double)row*10.0;
        item1->setData(Qt::EditRole, QVariant(itemValue));
        item1->setTextAlignment(Qt::AlignRight);
        m_tableWidget->setItem(row, 1, item1);
    }*/
}

QStandardItem *SampleTuningWidget::iterateSessionModel(const QModelIndex &parentIndex, QStandardItem *parentItem)
{
    Q_ASSERT(m_sampleModel);

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }


    for( int i_row = 0; i_row < m_sampleModel->rowCount( parentIndex ); ++i_row) {
        QModelIndex itemIndex = m_sampleModel->index( i_row, 0, parentIndex );



        if (ParameterizedItem *item = m_sampleModel->itemForIndex(itemIndex)){

            QStandardItem *standardItem = new QStandardItem(item->itemName());

            QList<QByteArray> propertyNameList = item->dynamicPropertyNames();
            for (int i = 0; i < propertyNameList.length(); ++i) {
                QString propertyName = QString(propertyNameList[i]);

                PropertyAttribute prop_attribute = item->getPropertyAttribute(propertyName);
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

                        qDebug() << "Item: " << item->itemName() << "SubItem:" << subItem->itemName();

                        QStandardItem *childStandardItem = new QStandardItem(subItem->itemName());

                        QList<QByteArray> childPropertyList = subItem->dynamicPropertyNames();

                        bool isChildPropertyFound = false;

                        for (int j = 0; j < childPropertyList.length(); ++j) {
                            QString childPropertyName = QString(childPropertyList[j]);

                            PropertyAttribute prop_attribute = item->getPropertyAttribute(childPropertyName);
                            if(prop_attribute.getAppearance() & PropertyAttribute::HiddenProperty) continue;

//                            if(subItem->getPropertyAttribute(childPropertyName) & ParameterizedItem::HiddenProperty) continue;



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
            iterateSessionModel(itemIndex, standardItem);

        }

    }

    return parentItem;
}


//QStandardItemModel *TestView::getItemModelFromSessionModel()
//{

//    QStandardItemModel *model = new QStandardItemModel(this);
//    model->setHorizontalHeaderItem( 0, new QStandardItem( "Property" ) );
//    model->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );
//    model->appendRow(iterateSessionModel());

//    return model;
//}

void SampleTuningWidget::insertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem)
{
    if(childValueItem == NULL)
    {
        childValueItem = new QStandardItem();
        childValueItem->setEditable(false);
    }

    parentItem->appendRow(QList<QStandardItem *>()  << childTitleItem << childValueItem);

}

void SampleTuningWidget::insertRowIntoItem(QStandardItem *parentItem, QString title, QVariant value, ParameterizedItem *parameterizedItem)
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

//QStandardItemModel *SampleTuningWidget::getTestItemModel()
//{
//    QStandardItemModel *model = new QStandardItemModel(this);
//    model->setHorizontalHeaderItem( 0, new QStandardItem( "Property" ) );
//    model->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );

//    QStandardItem *formFactorItem = new QStandardItem(QString("Form Factor"));


//    QStandardItem *lengthTitleItem = new QStandardItem(QString("Length"));
//    QStandardItem *lengthValueItem = new QStandardItem();
//    lengthValueItem->setData(QVariant(10.0), Qt::EditRole);
//    lengthValueItem->setEditable(true);

//    QStandardItem *heightTitleItem = new QStandardItem(QString("Height"));
//    QStandardItem *heightValueItem = new QStandardItem();
//    heightValueItem->setData(QVariant(20.0), Qt::EditRole);
//    heightValueItem->setEditable(true);

//    QStandardItem *widthTitleItem = new QStandardItem(QString("Width"));
//    QStandardItem *widthValueItem = new QStandardItem();
//    widthValueItem->setData(QVariant(30.0), Qt::EditRole);
//    widthValueItem->setEditable(true);

//    QList<QStandardItem *> lengthList;
//    lengthList << lengthTitleItem << lengthValueItem;
//    formFactorItem->appendRow(lengthList);

//    //formFactorItem->setChild(0,0,lengthTitleItem);
//    //formFactorItem->setChild(0,1,lengthValueItem);
//    formFactorItem->setChild(1,0,heightTitleItem);
//    formFactorItem->setChild(1,1,heightValueItem);
//    formFactorItem->setChild(2,0,widthTitleItem);
//    formFactorItem->setChild(2,1,widthValueItem);


//    QStandardItem *particleItem = new QStandardItem( QString("Particle"));
//    particleItem->appendRow(formFactorItem);

//    QStandardItem *layerItem = new QStandardItem( QString("Multilayer"));
//    layerItem->appendRow(particleItem);

//    model->appendRow(layerItem);

//    return model;
//}


void SampleTuningWidget::updateTreeView()
{
    m_treeView->setModel(0);

    delete m_parameterModel;
    m_parameterModel = createParameterModel();

    m_treeView->setModel(m_parameterModel);
    m_treeView->expandAll();
}

QStandardItemModel *SampleTuningWidget::createParameterModel()
{
    QStandardItemModel *result(0);
    result = new QStandardItemModel(this);
    result->setHorizontalHeaderItem( 0, new QStandardItem( "Property" ) );
    result->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );
    result->setItem(0, iterateSessionModel());
    return result;
}






