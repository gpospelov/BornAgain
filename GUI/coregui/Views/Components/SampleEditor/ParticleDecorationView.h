#ifndef PARTICLEDECORATIONVIEW_H
#define PARTICLEDECORATIONVIEW_H

#include "ISampleView.h"
#include <QLabel>

class QNEPort;


class ParticleDecorationView : public ISampleRectView
{
public:
    ParticleDecorationView(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
//    int getNumberOfOutputPorts();
//    int getNumberOfInputPorts();

    QString m_name;
    QColor m_color;
};


#endif // PARTICLEDECORATIONVIEW_H
