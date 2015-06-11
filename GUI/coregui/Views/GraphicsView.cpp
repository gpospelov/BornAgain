#include "GraphicsView.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"


//GraphicsView::GraphicsView() : m_rectangle(0), m_ellipse(0), m_polygon(0), isFinished(true),
//    m_currentMousePosition(QPointF(0,0)), m_lastAddedPoint(QPointF(0,0))
//{
//    m_drawing = NONE;
//}

//void GraphicsView::setDrawing(GraphicsView::Drawing drawing)
//{
//    m_drawing = drawing;
//}


//void GraphicsView::mousePressEvent(QMouseEvent *event)
//{
//    qDebug() << "GraphicsScene::mousePressEvent() ->" << m_drawing << m_rectangle;
//    if(m_drawing == RECTANGLE) {
//        m_rectangle = new Rectangle(this->mapToScene(event->pos()).x(), this->mapToScene(event->pos()).y(), 0,0);
//        scene()->addItem(m_rectangle);
//    }
//    else if(m_drawing == ELLIPSE) {
//        m_ellipse = new Ellipse(this->mapToScene(event->pos()).x(), this->mapToScene(event->pos()).y(), 0,0);
//        scene()->addItem(m_ellipse);
//    }
//    else if(m_drawing == POLYGON) {
//        if(isFinished) {
//            m_polygon = new Polygon(this->mapToScene(event->pos()).x(), this->mapToScene(event->pos()).y(), 0,0);
//            scene()->addItem(m_polygon);
//        }
//        m_polygon->setDrawingMode(this->mapToScene(event->pos()));
//        m_lastAddedPoint = this->mapToScene(event->pos());
//        isFinished = false;
//    }
//    else {
//        QGraphicsView::mousePressEvent(event);
//    }
//}

//void GraphicsView::mouseMoveEvent(QMouseEvent *event)
//{
////    qDebug() << "GraphicsScene::mouseMoveEvent() ->" << m_drawing << m_rectangle;
//    if(m_drawing == RECTANGLE && m_rectangle) {
//        m_rectangle->boundingRect().setWidth(this->mapToScene(event->pos()).x() - m_rectangle->boundingRect().topLeft().x());
//        m_rectangle->setWidth(this->mapToScene(event->pos()).x() - m_rectangle->boundingRect().topLeft().x());
//        m_rectangle->setHeigth(this->mapToScene(event->pos()).y() - m_rectangle->boundingRect().topLeft().y());
//    }
//    else if(m_drawing == ELLIPSE && m_ellipse) {
//        m_ellipse->setWidth(this->mapToScene(event->pos()).x() - m_ellipse->boundingRect().topLeft().x());
//        m_ellipse->setHeigth(this->mapToScene(event->pos()).y() - m_ellipse->boundingRect().topLeft().y());
//    }
//    else if(m_drawing == POLYGON && m_polygon) {
////        m_polygon->setWidth(event->scenePos().x() - m_polygon->boundingRect().topLeft().x());
////        m_polygon->setHeigth(event->scenePos().y() - m_polygon->boundingRect().topLeft().y());

////        QPainter painter;
////        painter.setPen(QPen(Qt::darkBlue, 2, Qt::DashLine));
////        painter.drawLine(QLineF(m_lastAddedPoint, event->scenePos()));
////        painter.end();
//    }
//    else {
//        QGraphicsView::mouseMoveEvent(event);
//    }
//    m_currentMousePosition =this->mapToScene(event->pos());
//}

//void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
//{
//    qDebug() << "GraphicsScene::mouseReleaseEvent() ->" << m_drawing << m_rectangle;
//    if(m_drawing != POLYGON) {
//        m_rectangle = 0;
//        m_ellipse = 0;
//        m_polygon = 0;
//        m_drawing = NONE;
//    }
//    QGraphicsView::mouseReleaseEvent(event);
//}

void GraphicsView::wheelEvent(QWheelEvent *event)
{

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;

    if(event->delta() > 0) {
        // Zoom in
        this->scale(scaleFactor, scaleFactor);

    } else {
        // Zooming out
        this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

//void GraphicsView::drawForeground(QPainter* painter, const QRectF& /* rect */)
//{
//    if(m_drawing == POLYGON && !isFinished) {
//        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
//        painter->drawLine(QLineF(m_lastAddedPoint, m_currentMousePosition));
//        this->invalidateScene();
//    }
