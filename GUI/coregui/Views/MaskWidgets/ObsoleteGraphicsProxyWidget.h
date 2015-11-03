#include "DistributionEditor.h"

#ifndef OBSOLETEGRAPHICSPROXYWIDGET_H
#define OBSOLETEGRAPHICSPROXYWIDGET_H

class ObsoleteGraphicsProxyWidget : public QGraphicsProxyWidget
{
public:
    //! Type of this item
    enum { Type = UserType + 4 };

    //! returns the type of this item
    //! @return number of type
    int type() const
    {
        return Type;
    }

protected:
    //! manages mouse press events
    //! @param event from scene
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //! manages mouse move events
    //! @param event from scene
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //! manages mouse release events
    //! @param event from scene
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif
