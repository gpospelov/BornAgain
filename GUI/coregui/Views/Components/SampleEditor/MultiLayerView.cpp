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
#include <QDropEvent>

#include "LayerView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"


bool sort_layers(QGraphicsItem* left, QGraphicsItem *right) {
    return left->y() < right->y();
}


MultiLayerView::MultiLayerView(QGraphicsItem *parent)
    : QGraphicsObject(parent), m_color(Qt::blue)
    , m_rect(0, 0, DesignerHelper::getMultiLayerWidth(), DesignerHelper::getMultiLayerHeight())
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

    int xpos = (DesignerHelper::getMultiLayerWidth() - DesignerHelper::getLayerWidth())/2.;
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
        total_height = DesignerHelper::getMultiLayerHeight();
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
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, rect() ) );
    painter->drawRect(rect());
}


void MultiLayerView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        std::cout << "MultiLayerView::dragEnterEvent() -> INSIDE " << std::endl;
    }


//    if (event->mimeData()->hasFormat("widgets/x-puzzle-piece")  && isInDropArea(event->pos())){
//        event->setAccepted(true);
//        std::cout << "MultiLayerView::dragEnterEvent() -> INSIDE " << std::endl;
//    } else {
//        event->setAccepted(false);
//    }
}


void MultiLayerView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "MultiLayerView::dragLeaveEvent() -> " << std::endl;
}


void MultiLayerView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        addLayer(new LayerView(), event->pos());
        update();
    }


//    if (event->mimeData()->hasFormat("image/x-puzzle-piece") && isInDropArea(event->pos()) ){
//        std::cout << "MultiLayerView::dropEvent() -> " <<  event->pos().x() << " " << event->pos().y() << std::endl;

//        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
//        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);

//        QString name;
//        QString xml;
//        QPoint global_mouse_pos;

//        dataStream >> name >> xml >> global_mouse_pos;

//        addLayer(new LayerView(), event->pos());
//        update();
//        event->setAccepted(true);
//    } else {
//        event->setAccepted(false);

//    }
}


void MultiLayerView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        std::cout << "MultiLayerView::dragMoveEvent() -> pos:" << event->pos().x() << " " << event->pos().y() << std::endl;
        update();

    }

//    if (event->mimeData()->hasFormat("image/x-puzzle-piece")  && isInDropArea(event->pos())){
//        std::cout << "MultiLayerView::dragMoveEvent() -> pos:" << event->pos().x() << " " << event->pos().y() << std::endl;
//        update();
//        event->setAccepted(true);
//    } else {
//        event->setAccepted(false);
//    }
}


void MultiLayerView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    std::cout << "MultiLayerView::mouseMoveEvent" << std::endl;
}



const DesignerMimeData *MultiLayerView::checkDragEvent(QGraphicsSceneDragDropEvent * event)
{
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
    }

    if(mimeData->hasFormat("widget/Layer")) {
        event->setAccepted(true);
//        mimeData->acceptEvent(event);
    } else {
        event->setAccepted(false);
    }
    return mimeData;
}

