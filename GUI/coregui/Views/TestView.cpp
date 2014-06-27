#include "TestView.h"
#include "TestViewDelegate.h"
#include "qitemselectionmodel.h"

TestView::TestView(QWidget *parent)
    : QWidget(parent)
    //, m_delegate(new TestViewDelegate(this))
{
    /*QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(1);
    model->setRowCount(5);
    model->setData(model->index(0, 0), "some data0");
    model->setData(model->index(1, 0), "some data1");
    model->setData(model->index(2, 0), "some data2");
    model->setData(model->index(3, 0), "some data3");
    model->setData(model->index(4, 0), "some data4");*/

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem( 0, new QStandardItem( "Name" ) );
    model->setHorizontalHeaderItem( 1, new QStandardItem( "Value" ) );

      /*for( int r=0; r<5; r++ )
        for( int c=0; c<2; c++)
        {
          QStandardItem *item = new QStandardItem( QString("Row:%0, Column:%1").arg(r).arg(c) );

          if( c == 0 )
            for( int i=0; i<3; i++ )
            {
              QStandardItem *child = new QStandardItem( QString("Item %0").arg(i) );
              child->setEditable( false );
              item->appendRow( child );
            }

          model->setItem(r, c, item);
        }*/

    QStandardItem *formFactorItem = new QStandardItem(QString("Form Factor"));

    //QStandardItem *heightValueItem = new QStandardItem(QString::number(2.3));

    QStandardItem *lengthTitleItem = new QStandardItem(QString("Length"));
    QStandardItem *lengthValueItem = new QStandardItem();
    lengthValueItem->setData(QVariant(10.0), Qt::EditRole);
    lengthValueItem->setEditable(true);

    QStandardItem *heightTitleItem = new QStandardItem(QString("Height"));
    QStandardItem *heightValueItem = new QStandardItem();
    heightValueItem->setData(QVariant(20.0), Qt::EditRole);
    heightValueItem->setEditable(false);



    //QStandardItem *heightValueItem = new QStandardItem();
    //QVariant heightVariant(1.7);
    //heightValueItem->setData(heightVariant);

    //QList<QStandardItem *> lengthList;
    //lengthList << lengthTitleItem << lengthValueItem;

    formFactorItem->setChild(0,0,lengthTitleItem);
    formFactorItem->setChild(0,1,lengthValueItem);
    formFactorItem->setChild(1,0,heightTitleItem);
    formFactorItem->setChild(1,1,heightValueItem);


    QStandardItem *particleItem = new QStandardItem( QString("Particle"));
    particleItem->appendRow(formFactorItem);

    QStandardItem *layerItem = new QStandardItem( QString("Multilayer"));
    layerItem->appendRow(particleItem);

    model->setItem(0,0,layerItem);

    QTreeView *treeView = new QTreeView(this);
    treeView->setModel(model);
    treeView->setFixedWidth(350);
    treeView->setColumnWidth(0,200);
    //treeView->setColumnWidth(1,100);
    treeView->expandAll();

    //QItemSelectionModel *selectionModel = treeView->selectionModel();

    m_delegate = new TestViewDelegate(this, treeView->selectionModel());

    treeView->setItemDelegateForColumn(1, m_delegate);
}




