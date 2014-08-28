#ifndef VECTORITEM_H
#define VECTORITEM_H


#include "ParameterizedItem.h"

class BA_CORE_API_  VectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_X;
    static const QString P_Y;
    static const QString P_Z;
    explicit VectorItem(ParameterizedItem *parent=0);
    ~VectorItem(){}
    QString getItemLabel() const;
};



#endif

