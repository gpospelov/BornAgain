#ifndef PARAMETERIZEDGRAPHICSITEM_h
#define PARAMETERIZEDGRAPHICSITEM_h


#include "ParameterizedItem.h"


class ParameterizedGraphicsItem : public ParameterizedItem
{
public:

protected:
    explicit ParameterizedGraphicsItem(const QString &model_type=QString(),
                               ParameterizedItem *parent=0)
        : ParameterizedItem(model_type, parent) , m_xpos(0), m_ypos (0) {}


private:
    int m_xpos;
    int m_ypos;
};

#endif


