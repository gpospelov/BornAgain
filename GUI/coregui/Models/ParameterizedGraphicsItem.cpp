#include "ParameterizedGraphicsItem.h"


const QString ParameterizedGraphicsItem::P_XPOS = "xpos";
const QString ParameterizedGraphicsItem::P_YPOS = "ypos";


ParameterizedGraphicsItem::ParameterizedGraphicsItem(const QString &model_type,
                           ParameterizedItem *parent)
    : ParameterizedItem(model_type, parent)
{
    registerProperty(P_XPOS, qreal(0.0), QString(), ParameterizedItem::HiddenProperty);
    registerProperty(P_YPOS, qreal(0.0), QString(), ParameterizedItem::HiddenProperty);
}

