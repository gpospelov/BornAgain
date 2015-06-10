#include "GraphicsView.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include <iostream>


GraphicsView::GraphicsView() : m_rectangle(0), m_ellipse(0), m_polygon(0)
{
    m_drawing = NONE;
}

void GraphicsView::setDrawing(GraphicsView::Drawing drawing)
{
    m_drawing = drawing;
}


void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(m_drawing == RECTANGLE) {
        QPointF point(mapToScene(event->pos()));
        scene()->addItem(new Rectangle(point.x(), point.y(), 0,0));
    }
        QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_drawing == RECTANGLE) {
        QList<QGraphicsItem *> items = this->scene()->items();
        for(int i = 0; i < items.length() -1; ++i) {
            if(items[0]->type() == Rectangle::Type) {
                Rectangle *rectangle = qgraphicsitem_cast<Rectangle*>(items[0]);
                rectangle->setWidth(event->screenPos().x() - rectangle->boundingRect().topLeft().x());
                rectangle->setHeigth(event->screenPos().y() - rectangle->boundingRect().topLeft().y());
                std::cout << rectangle->boundingRect().width() << std::endl;
            }

        }
    }



//        m_rectangle->boundingRect().setBottomRight(event->pos());


    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if( m_drawing == RECTANGLE) {
        m_rectangle = 0;
        m_drawing = NONE;
    }
    QGraphicsView::mouseReleaseEvent(event);
}
