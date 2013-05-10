#include "HomogeneousLayerView.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QCursor>
#include <QApplication>
#include <QMimeData>
#include <QBitmap>
#include <QWidget>
#include <QGradient>

HomogeneousLayerView::HomogeneousLayerView()
    : m_color(Qt::red)
    , m_rect(0, 0, 200, 50)
{
//    setToolTip(QString("QColor(%1, %2, %3)\n%4")
//              .arg(color.red()).arg(color.green()).arg(color.blue())
//              .arg("Do something"));
//    setCursor(Qt::OpenHandCursor);
//    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);

}

QRectF HomogeneousLayerView::boundingRect() const
{
    return rect();
}

void HomogeneousLayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(gradient(m_color, rect() ) );
    painter->drawRect(rect());
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(Qt::darkGray);
//    painter->drawEllipse(-12, -12, 30, 30);
//    painter->setPen(QPen(Qt::black, 1));
//    painter->setBrush(QBrush(color));
//    painter->drawEllipse(-15, -15, 30, 30);
}


QGradient HomogeneousLayerView::gradient(const QColor &color, const QRect &rect)
{
    QColor c = color;
    c.setAlpha(160);
    QLinearGradient result(rect.topLeft(), rect.bottomRight());
    result.setColorAt(0, c.dark(150));
    result.setColorAt(0.5, c.light(200));
    result.setColorAt(1, c.dark(150));
    return result;
}

//void ParticleView::mousePressEvent(QGraphicsSceneMouseEvent *)
//{
//    setCursor(Qt::ClosedHandCursor);
//}


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


