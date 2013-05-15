#include "MultiLayerView.h"

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

#include "LayerView.h"
#include "editorhelper.h"


bool sort_layers(QGraphicsItem* left, QGraphicsItem *right) {
    return left->y() < right->y();
}


MultiLayerView::MultiLayerView(QGraphicsItem *parent)
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

    LayerView * layer = new LayerView();
    addLayer(layer);
    addLayer(new LayerView());

    connect(this, SIGNAL(childrenChanged()), this, SLOT(updateHeight()));
    updateHeight();
}


void MultiLayerView::addLayer(LayerView *layer, QPointF pos)
{
    // adjusting main rectangle othervise item->setPos will not work due to 'LayerView::itemChange'
    m_rect.setHeight(m_rect.height()+layer->boundingRect().height());

    int xpos = (EditorHelper::getMultiLayerWidth() - EditorHelper::getLayerWidth())/2.;
    layer->setPos(xpos, pos.y());
    layer->setFixedX();
    connect(layer, SIGNAL(LayerMoved()), this, SLOT(updateHeight()) );
    layer->setParentItem(this);
}


// adjusts positions of Layers inside MultiLayer, updates total MultiLayer height
// calculates drop areas for new layers
// called when one of Layer is changed
void MultiLayerView::updateHeight()
{
    std::cout << "MultiLayerView::updateHeight() " << std::endl;
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


bool MultiLayerView::isInDropArea(QPointF pos)
{
    foreach(QRectF rect, m_drop_areas) {
        //std::cout << " drop areas " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height() << " point" << pos.x() << " " << pos.y() << std::endl;
        if (rect.contains(pos)) return true;
    }
    return false;
}


QRectF MultiLayerView::boundingRect() const
{
    return rect();
}


void MultiLayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::blue);
    painter->setBrush(gradient(m_color, rect() ) );
    painter->drawRect(rect());
}


QGradient MultiLayerView::gradient(const QColor &color, const QRect &rect)
{
    QColor c = color;
    c.setAlpha(160);
    QLinearGradient result(rect.topLeft(), rect.bottomRight());
    result.setColorAt(0, c.dark(150));
    result.setColorAt(0.5, c.light(200));
    result.setColorAt(1, c.dark(150));
    return result;
}

void MultiLayerView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")  && isInDropArea(event->pos())){
        event->setAccepted(true);
        std::cout << "MultiLayerView::dragEnterEvent() -> INSIDE " << std::endl;
    } else {
        event->setAccepted(false);
    }
}


void MultiLayerView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "MultiLayerView::dragLeaveEvent() -> " << std::endl;
}


void MultiLayerView::dropEvent(QGraphicsSceneDragDropEvent *event)
{

    if (event->mimeData()->hasFormat("image/x-puzzle-piece") && isInDropArea(event->pos()) ){
        std::cout << "MultiLayerView::dropEvent() -> " <<  event->pos().x() << " " << event->pos().y() << std::endl;

        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);

        QString name;
        QString xml;
        QPoint global_mouse_pos;

        dataStream >> name >> xml >> global_mouse_pos;

        addLayer(new LayerView(), event->pos());
        update();
        event->setAccepted(true);
    } else {
        event->setAccepted(false);

    }
}


void MultiLayerView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")  && isInDropArea(event->pos())){
        std::cout << "MultiLayerView::dragMoveEvent() -> pos:" << event->pos().x() << " " << event->pos().y() << std::endl;
        update();
        event->setAccepted(true);
    } else {
        event->setAccepted(false);

    }

}


void MultiLayerView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "MultiLayerView::mouseMoveEvent" << std::endl;
}


