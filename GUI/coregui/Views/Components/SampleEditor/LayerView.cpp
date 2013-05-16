#include "LayerView.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QCursor>
#include <QApplication>
#include <QMimeData>
#include <QBitmap>
#include <QWidget>
#include <QGradient>
#include <QStyleOptionGraphicsItem>

#include "DesignerHelper.h"
#include <iostream>


LayerView::LayerView(QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , m_color(qrand() % 256, qrand() % 256, qrand() % 256)
    , m_rect(0, 0, DesignerHelper::getLayerWidth(), DesignerHelper::getLayerHeight())
    , m_fixed_xpos(0)
{
//    setToolTip(QString("QColor(%1, %2, %3)\n%4")
//              .arg(color.red()).arg(color.green()).arg(color.blue())
//              .arg("Do something"));
//    setCursor(Qt::OpenHandCursor);
//    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptDrops(false);
}

QRectF LayerView::boundingRect() const
{
    return rect();
}

void LayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getLayerGradient(m_color, rect() ) );
    painter->drawRect(rect());
}


void LayerView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerView::mouseMoveEvent -> " << x() << " " << y() << std::endl;
    QGraphicsObject::mouseMoveEvent(event);
}

void LayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerView::mousePressEvent -> " << x() << " " << y() << std::endl;
    QGraphicsObject::mousePressEvent(event);
}

void LayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerView::mouseReleaseEvent -> " << x() << " " << y() << std::endl;
    emit LayerMoved();
    QGraphicsObject::mouseReleaseEvent(event);
//    setCursor(Qt::ArrowCursor);
}


void LayerView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerView::dragEnterEvent() ->" << std::endl;
}

void LayerView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerView::dragLeaveEvent() ->" << std::endl;
}

void LayerView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerView::dropEvent() ->" << std::endl;

}

void LayerView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerView::dragMoveEvent() ->" << std::endl;
}


QVariant LayerView::itemChange(GraphicsItemChange change, const QVariant &value)
 {
     if (change == ItemPositionChange && scene()) {
         //std::cout << "YYY itemChange " << x() << " " << y() <<  std::endl;
         // value is the new position.
         QPointF newPos = value.toPointF();
         QRectF rect = parentItem()->boundingRect();
         //std::cout << "rect " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height() << std::endl;
         rect.setY(rect.y() - boundingRect().height()/2.);
         rect.setHeight(rect.height() - boundingRect().height()/2.);
         //std::cout << "rect " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height() << std::endl;
         if (!rect.contains(newPos)) {
             // Keep the item inside the scene rect.
             newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
         }
         newPos.setX(m_fixed_xpos);
         return newPos;
     }
     return QGraphicsItem::itemChange(change, value);
 }


//void ParticleView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
//        .length() < QApplication::startDragDistance()) {
//        return;
//    }

//    QDrag *drag = new QDrag(event->widget());
//    QMimeData *mime = new QMimeData;
//    drag->setMimeData(mime);

//    static int n = 0;
//    if (n++ > 2 && (qrand() % 3) == 0) {
//        QImage image(":/images/head.png");
//        mime->setImageData(image);

//        drag->setPixmap(QPixmap::fromImage(image).scaled(30, 40));
//        drag->setHotSpot(QPoint(15, 30));

//    } else {
//        mime->setColorData(color);
//        mime->setText(QString("#%1%2%3")
//                      .arg(color.red(), 2, 16, QLatin1Char('0'))
//                      .arg(color.green(), 2, 16, QLatin1Char('0'))
//                      .arg(color.blue(), 2, 16, QLatin1Char('0')));

//        QPixmap pixmap(34, 34);
//        pixmap.fill(Qt::white);

//        QPainter painter(&pixmap);
//        painter.translate(15, 15);
//        painter.setRenderHint(QPainter::Antialiasing);
//        paint(&painter, 0, 0);
//        painter.end();

//        pixmap.setMask(pixmap.createHeuristicMask());

//        drag->setPixmap(pixmap);
//        drag->setHotSpot(QPoint(15, 20));
//    }

//    drag->exec();
//    setCursor(Qt::OpenHandCursor);
//}


//void ParticleView::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
//{
//    setCursor(Qt::OpenHandCursor);
//}


