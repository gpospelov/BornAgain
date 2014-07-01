#ifndef PARTICLECORESHELLITEM_H
#define PARTICLECORESHELLITEM_H

#include "ParameterizedGraphicsItem.h"
#include <QVector>

class ParticleCoreShellItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    enum CoreShell { Core, Shell};
    static const QString P_TYPE_NAME, P_CORE_X, P_CORE_Y, P_CORE_Z;
    explicit ParticleCoreShellItem(ParameterizedItem *parent=0);
    ~ParticleCoreShellItem(){}
};


#endif

