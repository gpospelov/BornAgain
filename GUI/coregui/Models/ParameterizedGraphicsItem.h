#ifndef PARAMETERIZEDGRAPHICSITEM_h
#define PARAMETERIZEDGRAPHICSITEM_h


#include "ParameterizedItem.h"


class ParameterizedGraphicsItem : public ParameterizedItem
{
    Q_OBJECT
public:

protected:
    explicit ParameterizedGraphicsItem(const QString &model_type=QString(),
                               ParameterizedItem *parent=0)
        : ParameterizedItem(model_type, parent)
    {
        setProperty("xpos", qreal(0.0));
        setProperty("ypos", qreal(0.0));
    }
};

#endif


