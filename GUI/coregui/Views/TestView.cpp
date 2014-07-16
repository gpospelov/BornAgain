#include "TestView.h"
#include "qitemselectionmodel.h"
#include "TestViewDelegate.h"
#include "qdebug.h"

TestView::TestView(QWidget *parent)
    : QWidget(parent)
{


    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem( 0, new QStandardItem( "Name" ) );
    model->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );

    QStandardItem *formFactorItem = new QStandardItem(QString("Form Factor"));

    //QStandardItem *heightValueItem = new QStandardItem(QString::number(2.3));

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



    //QStandardItem *heightValueItem = new QStandardItem();
    //QVariant heightVariant(1.7);
    //heightValueItem->setData(heightVariant);

    //QList<QStandardItem *> lengthList;
    //lengthList << lengthTitleItem << lengthValueItem;

    formFactorItem->setChild(0,0,lengthTitleItem);
    formFactorItem->setChild(0,1,lengthValueItem);
    formFactorItem->setChild(1,0,heightTitleItem);
    formFactorItem->setChild(1,1,heightValueItem);
    formFactorItem->setChild(2,0,widthTitleItem);
    formFactorItem->setChild(2,1,widthValueItem);


    QStandardItem *particleItem = new QStandardItem( QString("Particle"));
    particleItem->appendRow(formFactorItem);

    QStandardItem *layerItem = new QStandardItem( QString("Multilayer"));
    layerItem->appendRow(particleItem);

    model->setItem(0,0,layerItem);


    //generate Tree View
    QTreeView *treeView = new QTreeView(this);
    treeView->setModel(model);
    treeView->setFixedWidth(350);
    treeView->setColumnWidth(0,180);
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




