#ifndef REFRACTIVEINDEXITEM_H
#define REFRACTIVEINDEXITEM_H


#include "ParameterizedItem.h"

class BA_CORE_API_ RefractiveIndexItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DELTA;
    static const QString P_BETA;
    explicit RefractiveIndexItem(ParameterizedItem *parent=0);
    ~RefractiveIndexItem(){}
    QString getItemLabel() const;

    double getDelta() const;
    void setDelta(double delta);

    double getBeta() const;
    void setBeta(double beta);
};



#endif
