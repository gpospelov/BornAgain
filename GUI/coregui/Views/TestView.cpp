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
#include "MaskEditor.h"
#include "MaskModel.h"
#include "RectangleItem.h"


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
    ParameterizedItem *rectangle = maskModel->insertNewItem(Constants::RectangleType);
    rectangle->setRegisteredProperty(RectangleItem::P_WIDTH, 100.0);
    rectangle->setRegisteredProperty(RectangleItem::P_HEIGHT, 200.0);

//    ParameterizedItem *polygon = maskModel->insertNewItem(Constants::PolygonType);
//    maskModel->insertNewItem(Constants::PointType, maskModel->indexOfItem(polygon));

//    maskModel->save("masks.xml");

//    Q_ASSERT(0);

    MaskEditor *maskEditor = new MaskEditor;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    mainLayout->addWidget(maskEditor);

}
