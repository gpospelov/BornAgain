#include "MultiLayerItem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QCursor>
#include <QApplication>
#include <QMimeData>
#include <QBitmap>
#include <QWidget>
#include <QGradient>
#include <iostream>

#include "HomogeneousLayerView.h"
#include "editorhelper.h"


bool sort_layers(QGraphicsItem* left, QGraphicsItem *right) {
    return left->y() < right->y();
}


MultiLayerItem::MultiLayerItem(QGraphicsItem *parent)
    : QGraphicsObject(parent), m_color(Qt::blue)
    , m_rect(0, 0, EditorHelper::getMultiLayerWidth(), EditorHelper::getMultiLayerHeight())
{
    setToolTip(QString("QColor(%1, %2, %3)\n%4")
              .arg(Qt::red).arg(Qt::green).arg(Qt::blue)
              .arg("Drag and drop the Layer object here"));
//    setCursor(Qt::OpenHandCursor);
//    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    setAcceptDrops(true);

    HomogeneousLayerView * layer = new HomogeneousLayerView();
    addLayer(layer);
    addLayer(new HomogeneousLayerView());

    connect(this, SIGNAL(childrenChanged()), this, SLOT(updateHeight()));
    updateHeight();
}


// add or append the layer
//void MultiLayerItem::addLayer(HomogeneousLayerView *layer, QPointF pos)
//{
//    QList<QGraphicsItem *> list = childItems();
//    qSort(list.begin(), list.end(), sort_layers);

//    int index = 0;
//    qreal max_dist(std::numeric_limits<qreal>::max());
//    for(int i=0; i<list.size(); ++i) {
//        // close to the top boundry of layer
//        if( max_dist > qAbs(pos.y() - list.at(i)->y())) {
//            max_dist = qAbs(pos.y() - list.at(i)->y());
//            index = i;
//        }
//        // close to the bottom layer boundary
//        if( max_dist > qAbs(pos.y() - (list.at(i)->y() + list.at(i)->boundingRect().height()) ) ) {
//            max_dist = qAbs(pos.y() - (list.at(i)->y() + list.at(i)->boundingRect().height()) );
//            index = i+1;
//        }

//    }
//    list.insert(index, layer);

//    // adjusting main rectangle othervise item->setPos will not work due to 'itemChange'
//    m_rect.setHeight(m_rect.height()+layer->boundingRect().height());

//    int total_height = 0;
//    int xpos = (EditorHelper::getMultiLayerWidth() - EditorHelper::getLayerWidth())/2.;
//    foreach(QGraphicsItem *item, list) {
//        item->setPos(xpos, total_height);
//        total_height += item->boundingRect().height();
//    }

//    layer->setFixedX();
//    layer->setParentItem(this);

//}



void MultiLayerItem::addLayer(HomogeneousLayerView *layer, QPointF pos)
{
    // adjusting main rectangle othervise item->setPos will not work due to 'itemChange'
    m_rect.setHeight(m_rect.height()+layer->boundingRect().height());

    int xpos = (EditorHelper::getMultiLayerWidth() - EditorHelper::getLayerWidth())/2.;
    layer->setPos(xpos, pos.y());
    layer->setFixedX();
    connect(layer, SIGNAL(LayerMoved()), this, SLOT(updateHeight()) );
    layer->setParentItem(this);


//    QList<QGraphicsItem *> list = childItems();
//    qSort(list.begin(), list.end(), sort_layers);

//    int index = 0;
//    qreal max_dist(std::numeric_limits<qreal>::max());
//    for(int i=0; i<list.size(); ++i) {
//        // close to the top boundry of layer
//        if( max_dist > qAbs(pos.y() - list.at(i)->y())) {
//            max_dist = qAbs(pos.y() - list.at(i)->y());
//            index = i;
//        }
//        // close to the bottom layer boundary
//        if( max_dist > qAbs(pos.y() - (list.at(i)->y() + list.at(i)->boundingRect().height()) ) ) {
//            max_dist = qAbs(pos.y() - (list.at(i)->y() + list.at(i)->boundingRect().height()) );
//            index = i+1;
//        }

//    }
//    list.insert(index, layer);

//    // adjusting main rectangle othervise item->setPos will not work due to 'itemChange'
//    m_rect.setHeight(m_rect.height()+layer->boundingRect().height());

//    int total_height = 0;
//    int xpos = (EditorHelper::getMultiLayerWidth() - EditorHelper::getLayerWidth())/2.;
//    foreach(QGraphicsItem *item, list) {
//        item->setPos(xpos, total_height);
//        total_height += item->boundingRect().height();
//    }

//    layer->setFixedX();
//    layer->setParentItem(this);

//    connect(layer, SIGNAL(yChanged()), this, SLOT(adjustLayerCoordinate(HomogeneousLayerView *layer)) );
//    connect(layer, SIGNAL(LayerMoved()), this, SLOT(adjustLayerCoordinate()) );
//    connect(layer, SIGNAL(LayerMoved()), this, SLOT(updateHeight()) );

}



//void MultiLayerItem::adjustLayerCoordinate()
//{
//    std::cout << " MultiLayerItem::adjustLayerCoordinate() -> " << std::endl;
//    updateHeight();
//}



// adjusts positions of Layers inside MultiLayer, updates total MultiLayer height
// calculates drop areas for new layers
// called when one of Layer is changed
void MultiLayerItem::updateHeight()
{
    std::cout << "MultiLayerItem::updateHeight() " << std::endl;
    // drop areas are rectangles covering the area of layer interfaces
    m_drop_areas.clear();

    QList<QGraphicsItem *> list = childItems();
    qSort(list.begin(), list.end(), sort_layers);

    int total_height = 0;
    if( childItems().size() > 0) {
        foreach(QGraphicsItem *item, list) {
            item->setY(total_height);
            total_height += item->boundingRect().height();
            m_drop_areas.append(QRectF(0, item->y() - item->boundingRect().height()/4., boundingRect().width(), item->boundingRect().height()/2.));
        }
        m_drop_areas.append(QRectF(0, list.back()->y() +list.back()->boundingRect().height() - list.back()->boundingRect().height()/4., boundingRect().width(), list.back()->boundingRect().height()/2.));
    } else {
        total_height = EditorHelper::getMultiLayerHeight();
        m_drop_areas.append(boundingRect());
    }

    m_rect.setHeight(total_height);
    update();
}


bool MultiLayerItem::isInDropArea(QPointF pos)
{
    foreach(QRectF rect, m_drop_areas) {
        //std::cout << " drop areas " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height() << " point" << pos.x() << " " << pos.y() << std::endl;
        if (rect.contains(pos)) return true;
    }
    return false;
}


QRectF MultiLayerItem::boundingRect() const
{
    return rect();
}


void MultiLayerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::blue);
    painter->setBrush(gradient(m_color, rect() ) );
    painter->drawRect(rect());
}


QGradient MultiLayerItem::gradient(const QColor &color, const QRect &rect)
{
    QColor c = color;
    c.setAlpha(160);
    QLinearGradient result(rect.topLeft(), rect.bottomRight());
    result.setColorAt(0, c.dark(150));
    result.setColorAt(0.5, c.light(200));
    result.setColorAt(1, c.dark(150));
    return result;
}

void MultiLayerItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")  && isInDropArea(event->pos())){
        event->setAccepted(true);
        std::cout << "MultiLayerItem::dragEnterEvent() -> INSIDE " << std::endl;
    } else {
        event->setAccepted(false);
    }
}


void MultiLayerItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "MultiLayerItem::dragLeaveEvent() -> " << std::endl;
}


void MultiLayerItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{

    if (event->mimeData()->hasFormat("image/x-puzzle-piece") && isInDropArea(event->pos()) ){
        std::cout << "MultiLayerItem::dropEvent() -> " <<  event->pos().x() << " " << event->pos().y() << std::endl;

        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);

        QString name;
        QString xml;
        QPoint global_mouse_pos;

        dataStream >> name >> xml >> global_mouse_pos;

        addLayer(new HomogeneousLayerView(), event->pos());
        update();
        event->setAccepted(true);
    } else {
        event->setAccepted(false);

    }
}


void MultiLayerItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")  && isInDropArea(event->pos())){
        std::cout << "MultiLayerItem::dragMoveEvent() -> pos:" << event->pos().x() << " " << event->pos().y() << std::endl;
        update();
        event->setAccepted(true);
    } else {
        event->setAccepted(false);

    }

}


void MultiLayerItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "MultiLayerItem::mouseMoveEvent" << std::endl;
}


