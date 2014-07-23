#ifndef REFRACTIVEINDEXITEM_H
#define REFRACTIVEINDEXITEM_H


#include "ParameterizedItem.h"

class RefractiveIndexItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DELTA, P_BETA;
    explicit RefractiveIndexItem(ParameterizedItem *parent=0);
    ~RefractiveIndexItem(){}
    QString getItemLabel() const;
    double getDelta() const;
    double getBeta() const;
};



#endif
