#ifndef PARTICLEVIEW_H
#define PARTICLEVIEW_H


#include <QGraphicsItem>

//- -------------------------------------------------------------------
//! @class ParticleView
//! @brief Graphics representation of Particle in SampleEditorScene
//- -------------------------------------------------------------------
class ParticleView : public QGraphicsItem
{
public:

    ParticleView();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
};

#endif // PARTICLEVIEW_H
