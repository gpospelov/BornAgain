#ifndef TRANSFORMATIONITEM_H
#define TRANSFORMATIONITEM_H

#include "ParameterizedGraphicsItem.h"
#include <QVector>

class TransformationItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    static const QString P_POS, P_ROT;
    explicit TransformationItem(ParameterizedItem *parent=0);
    ~TransformationItem(){}
};


#endif // TRANSFORMATIONITEM_H

