#ifndef PARAMETERIZEDGRAPHICSITEM_h
#define PARAMETERIZEDGRAPHICSITEM_h


#include "ParameterizedItem.h"


class BA_CORE_API_ ParameterizedGraphicsItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_XPOS;
    static const QString P_YPOS;

protected:
    explicit ParameterizedGraphicsItem(const QString &model_type=QString(),
                               ParameterizedItem *parent=0);
};

#endif


