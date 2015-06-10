#include "GraphicsScene.h"
#include "Rectangle.h"


GraphicsScene::GraphicsScene() : m_rectangle(0), m_ellipse(0), m_polygon(0)
{
    m_drawing = NONE;
}


void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(RECTANGLE) {
        m_rectangle = new Rectangle(event->pos().x(), event->pos().y(), 100,100);
        this->addItem(m_rectangle);
    }
    else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(RECTANGLE) {
        m_rectangle->boundingRect().bottomRight() = event->pos();
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(RECTANGLE) {
        m_rectangle = 0;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

