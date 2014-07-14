#ifndef VECTORITEM_H
#define VECTORITEM_H


#include "ParameterizedItem.h"

class VectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_TYPE_NAME, P_X, P_Y, P_Z;
    explicit VectorItem(ParameterizedItem *parent=0);
    ~VectorItem(){}
};



#endif

