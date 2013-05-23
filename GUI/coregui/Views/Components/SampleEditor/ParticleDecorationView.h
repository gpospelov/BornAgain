#ifndef PARTICLEDECORATIONVIEW_H
#define PARTICLEDECORATIONVIEW_H

#include "ISampleView.h"
#include <QLabel>

class QNEPort;


class ParticleDecorationView : public ISampleView
{
public:
    ParticleDecorationView(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QNEPort* addPort(const QString &name, bool isOutput, int flags = 0, int ptr = 0);


private:
    QRect rect() const { return m_rect;}

    int getNumberOfOutputPorts();
    int getNumberOfInputPorts();

    QString m_name;
    QColor m_color;
    QRect m_rect;

};


#endif // PARTICLEDECORATIONVIEW_H
