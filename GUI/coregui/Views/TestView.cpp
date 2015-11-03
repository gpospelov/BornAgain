// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "TestView.h"
#include "TestItem.h"
#include "LayerItem.h"
#include "AwesomePropertyEditor.h"
#include "BeamWavelengthItem.h"
#include "ParameterizedItem.h"
//#include <QGroupBox>
#include <QGridLayout>
#include <QDebug>
#include "DistributionEditor.h"
#include "qgroupbox.h"
#include "ObsoleteMaskEditor.h"
#include "MaskModel.h"
#include "RectangleItem.h"
#include "Rectangle.h"


TestView::TestView(QWidget *parent)
    : QWidget(parent)
//    , m_item(0)
{
    setMouseTracking(true);

//   QGraphicsScene *scene = new QGraphicsScene;
//   QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(
//   QPolygonF(QVector<QPointF>() << QPointF(10, 10) << QPointF(0, 90) << QPointF(40, 70)
//                                    << QPointF(80, 110) << QPointF(70, 20)),0);
//   polygonItem->setPen(QPen(Qt::darkGreen));
//   polygonItem->setBrush(Qt::transparent);
//   this->setScene(scene);
//   scene->itemsBoundingRect();

//   DistributionEditor *editor = new DistributionEditor;
//   editor->setItem(new BeamWavelengthItem);
//   editor->resize(800,600);
//   GraphicsProxyWidget *widget = new GraphicsProxyWidget;
//   widget->setWidget(editor);
//   scene->addItem(widget);

//   Rectangle *rectangle = new Rectangle(0,0,200,200);
//   scene->addItem(rectangle);
//   rectangle->setFlag(QGraphicsItem::ItemIsMovable);


//   polygonItem->setFlag(QGraphicsItem::ItemIsMovable);

//   Ellipse *ellipse = new Ellipse(0,0,100,50);
//   scene->addItem(ellipse);
//   ellipse->setFlag(QGraphicsItem::ItemIsMovable);

    MaskModel *maskModel = new MaskModel;
//    ParameterizedItem *rectangle1 = maskModel->insertNewItem(Constants::RectangleType);
//    rectangle1->setRegisteredProperty(RectangleItem::P_WIDTH, 100.0);
//    rectangle1->setRegisteredProperty(RectangleItem::P_HEIGHT, 200.0);
//    rectangle1->setItemName("rect1");
//    ParameterizedItem *rectangle2 = maskModel->insertNewItem(Constants::RectangleType);
//    rectangle2->setRegisteredProperty(RectangleItem::P_WIDTH, 120.0);
//    rectangle2->setRegisteredProperty(RectangleItem::P_HEIGHT, 220.0);
//    rectangle2->setItemName("rect2");
//    ParameterizedItem *rectangle3 = maskModel->insertNewItem(Constants::RectangleType);
//    rectangle3->setRegisteredProperty(RectangleItem::P_WIDTH, 120.0);
//    rectangle3->setRegisteredProperty(RectangleItem::P_HEIGHT, 220.0);
//    rectangle3->setItemName("rect3");


//    QModelIndex itemIndex = maskModel->index(1, 0, QModelIndex());
//    ParameterizedItem *item = maskModel->itemForIndex(itemIndex);
//    maskModel->moveParameterizedItem(item, 0, 3);

//    for (int i_row = 0; i_row < maskModel->rowCount(QModelIndex()); ++i_row) {
//        QModelIndex itemIndex = maskModel->index(i_row, 0, QModelIndex());

//        if (ParameterizedItem *item = maskModel->itemForIndex(itemIndex)) {

//            qDebug() << i_row << item->itemName();
//        }


//    Q_ASSERT(0);

//    ParameterizedItem *polygon = maskModel->insertNewItem(Constants::PolygonType);
//    maskModel->insertNewItem(Constants::PointType, maskModel->indexOfItem(polygon));

//    maskModel->save("masks.xml");

//    Q_ASSERT(0);

    ObsoleteMaskEditor *maskEditor = new ObsoleteMaskEditor;
    maskEditor->setModel(maskModel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
//    Rectangle *rectangle = new Rectangle(300,300,100,100);
//    QGraphicsScene *scene = new QGraphicsScene();
//    scene->addItem(rectangle);
//    QGraphicsView *view = new QGraphicsView;
//    view->setScene(scene);
//    scene->setSceneRect(view->rect());
    mainLayout->addWidget(maskEditor);

}
