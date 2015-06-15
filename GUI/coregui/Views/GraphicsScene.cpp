#include "GraphicsScene.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Polygon.h"

GraphicsScene::GraphicsScene()
    : m_rectangle(0), m_ellipse(0), m_polygon(0), isFinished(true),
      m_currentMousePosition(QPointF(0, 0)), m_lastAddedPoint(QPointF(0, 0))
{
    m_drawing = NONE;
}

void GraphicsScene::setDrawing(GraphicsScene::Drawing drawing)
{
    m_drawing = drawing;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "GraphicsScene::mousePressEvent() ->" << m_drawing << m_rectangle;
    if (m_drawing == RECTANGLE) {
        m_rectangle = new Rectangle(event->scenePos().x(), event->scenePos().y(), 0, 0);
        addItem(m_rectangle);
    } else if (m_drawing == ELLIPSE) {
        m_ellipse = new Ellipse(event->scenePos().x(), event->scenePos().y(), 0, 0);
        addItem(m_ellipse);
    } else if (m_drawing == POLYGON) {
        if (isFinished) {
            m_polygon = new Polygon(event->scenePos().x(), event->scenePos().y(), 0, 0);
            addItem(m_polygon);
            m_polygon->setDrawingMode(event->scenePos());
            m_lastAddedPoint = event->scenePos();
            isFinished = false;
        } else {
            m_polygon->setDrawingMode(event->scenePos());
            m_lastAddedPoint = event->scenePos();
        }
        isFinished = !m_polygon->getDrawingMode();
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "GraphicsScene::mouseMoveEvent() ->" << m_drawing << m_rectangle;
    if (m_drawing == RECTANGLE && m_rectangle) {
        m_rectangle->boundingRect().setWidth(event->scenePos().x()
                                             - m_rectangle->boundingRect().topLeft().x());
        m_rectangle->setWidth(event->scenePos().x() - m_rectangle->boundingRect().topLeft().x());
        m_rectangle->setHeigth(event->scenePos().y() - m_rectangle->boundingRect().topLeft().y());
    } else if (m_drawing == ELLIPSE && m_ellipse) {
        m_ellipse->setWidth(event->scenePos().x() - m_ellipse->boundingRect().topLeft().x());
        m_ellipse->setHeigth(event->scenePos().y() - m_ellipse->boundingRect().topLeft().y());
    } else if (m_drawing == POLYGON && m_polygon) {
        if (m_polygon->getFirstPoint().contains(event->scenePos())) {
            m_polygon->setMouseIsOverFirstPoint(true);
        }
        else {
            m_polygon->setMouseIsOverFirstPoint(false);
        }
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
    m_currentMousePosition = event->scenePos();
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "GraphicsScene::mouseReleaseEvent() ->" << m_drawing << m_rectangle;
    m_rectangle = 0;
    m_ellipse = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::drawForeground(QPainter *painter, const QRectF & /* rect */)
{
    if (m_drawing == POLYGON && !isFinished) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawLine(QLineF(m_lastAddedPoint, m_currentMousePosition));
        invalidate();
    } else {
        m_lastAddedPoint = m_currentMousePosition;
    }
}
