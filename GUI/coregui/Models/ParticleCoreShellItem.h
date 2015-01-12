#ifndef PARTICLECORESHELLITEM_H
#define PARTICLECORESHELLITEM_H

#include "ParameterizedGraphicsItem.h"
#include <QVector>

class BA_CORE_API_ ParticleCoreShellItem : public ParameterizedGraphicsItem
{
    Q_OBJECT
public:
    enum ECoreShell { CORE, SHELL};
    static const QString P_CORE_POS;
    explicit ParticleCoreShellItem(ParameterizedItem *parent=0);
    ~ParticleCoreShellItem(){}
    void insertChildItem(int row, ParameterizedItem *item);
};


#endif

