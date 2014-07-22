#ifndef MAGNETICFIELDITEM_H
#define MAGNETICFIELDITEM_H


#include "ParameterizedItem.h"

class MagneticFieldItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_BX, P_BY, P_BZ;
    explicit MagneticFieldItem(ParameterizedItem *parent=0);
    ~MagneticFieldItem(){}
    QString getItemLabel() const;
};



#endif

