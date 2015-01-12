#ifndef TRANSFORMATIONVIEW_H
#define TRANSFORMATIONVIEW_H


#include "ConnectableView.h"

class TransformationView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::TRANSFORMATION };

    TransformationView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }
};

#endif // TRANSFORMATIONVIEW_H
