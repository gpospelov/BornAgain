#ifndef FORMFACTORVIEW_H
#define FORMFACTORVIEW_H


#include <QGraphicsItem>
#include "ISampleView.h"

//- -------------------------------------------------------------------
//! @class FormFactorView
//! @brief Graphics representation of Particle in SampleEditorScene
//- -------------------------------------------------------------------
class FormFactorView : public ISampleView
{
public:

    FormFactorView();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
};

#endif // FORMFACTORVIEW_H
