#ifndef TRANSFORMATIONVIEW_H
#define TRANSFORMATIONVIEW_H


#include "ConnectableView.h"

class TransformationView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::TransformationType };

    TransformationView(QGraphicsItem *parent = 0);

    int type() const { return Type; }
};

#endif // TRANSFORMATIONVIEW_H
