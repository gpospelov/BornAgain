#ifndef MAGNETICFIELDITEM_H
#define MAGNETICFIELDITEM_H


#include "ParameterizedItem.h"

class BA_CORE_API_ MagneticFieldItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_BX;
    static const QString P_BY;
    static const QString P_BZ;
    explicit MagneticFieldItem(ParameterizedItem *parent=0);
    ~MagneticFieldItem(){}
    QString getItemLabel() const;
};



#endif

