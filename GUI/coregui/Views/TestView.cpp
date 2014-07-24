#include "TestView.h"
#include "qitemselectionmodel.h"
#include "PropertyAttribute.h"
#include "TestViewDelegate.h"
#include "qdebug.h"

TestView::TestView(SessionModel *sampleModel, QWidget *parent)
    : QWidget(parent)
    , m_sampleModel(sampleModel)
{

    //iterateSessionModel();
    //generate Tree View
    QTreeView *treeView = new QTreeView(this);
    //treeView->setModel(model);
    treeView->setModel(getItemModelFromSessionModel());
    //treeView->setModel(getTestItemModel());

    treeView->setFixedWidth(450);
    treeView->setFixedHeight(600);
    treeView->setColumnWidth(0,250);
    treeView->expandAll();

    //QItemSelectionModel *selectionModel = treeView->selectionModel();
    //m_delegate = new TestViewDelegate(this, treeView->selectionModel());
    //treeView->setItemDelegateForColumn(1, m_delegate);



    treeView->setItemDelegate(new TestViewDelegate(1));


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

QStandardItem *TestView::iterateSessionModel(const QModelIndex &parentIndex, QStandardItem *parentItem)
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
                    insertRowIntoItem(standardItem, propertyName, propertyValue);

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
                                insertRowIntoItem(childStandardItem, childPropertyName, childPropertyValue);
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


QStandardItemModel *TestView::getItemModelFromSessionModel()
{

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem( 0, new QStandardItem( "Property" ) );
    model->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );
    model->appendRow(iterateSessionModel());

    return model;
}

void TestView::insertRowIntoItem(QStandardItem *parentItem, QStandardItem *childTitleItem, QStandardItem *childValueItem)
{
    if(childValueItem == NULL)
    {
        childValueItem = new QStandardItem();
        childValueItem->setEditable(false);
    }

    parentItem->appendRow(QList<QStandardItem *>()  << childTitleItem << childValueItem);

}

void TestView::insertRowIntoItem(QStandardItem *parentItem, QString title, QVariant value)
{
    QStandardItem *titleItem = new QStandardItem(title);
    QStandardItem *valueItem = new QStandardItem();
    valueItem->setData(value, Qt::EditRole);
    valueItem->setEditable(true);
    insertRowIntoItem(parentItem, titleItem, valueItem);

}

QStandardItemModel *TestView::getTestItemModel()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem( 0, new QStandardItem( "Property" ) );
    model->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );

    QStandardItem *formFactorItem = new QStandardItem(QString("Form Factor"));


    QStandardItem *lengthTitleItem = new QStandardItem(QString("Length"));
    QStandardItem *lengthValueItem = new QStandardItem();
    lengthValueItem->setData(QVariant(10.0), Qt::EditRole);
    lengthValueItem->setEditable(true);

    QStandardItem *heightTitleItem = new QStandardItem(QString("Height"));
    QStandardItem *heightValueItem = new QStandardItem();
    heightValueItem->setData(QVariant(20.0), Qt::EditRole);
    heightValueItem->setEditable(true);

    QStandardItem *widthTitleItem = new QStandardItem(QString("Width"));
    QStandardItem *widthValueItem = new QStandardItem();
    widthValueItem->setData(QVariant(30.0), Qt::EditRole);
    widthValueItem->setEditable(true);

    QList<QStandardItem *> lengthList;
    lengthList << lengthTitleItem << lengthValueItem;
    formFactorItem->appendRow(lengthList);

    //formFactorItem->setChild(0,0,lengthTitleItem);
    //formFactorItem->setChild(0,1,lengthValueItem);
    formFactorItem->setChild(1,0,heightTitleItem);
    formFactorItem->setChild(1,1,heightValueItem);
    formFactorItem->setChild(2,0,widthTitleItem);
    formFactorItem->setChild(2,1,widthValueItem);


    QStandardItem *particleItem = new QStandardItem( QString("Particle"));
    particleItem->appendRow(formFactorItem);

    QStandardItem *layerItem = new QStandardItem( QString("Multilayer"));
    layerItem->appendRow(particleItem);

    model->appendRow(layerItem);

    return model;

}







