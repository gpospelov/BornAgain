// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/SizeHandleElement.h
//! @brief     Defines SizeHandleElement class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIZEHANDLEELEMENT_H
#define SIZEHANDLEELEMENT_H

#include "IMaskView.h"
#include "DesignerHelper.h"
#include <QCursor>
#include <QGraphicsObject>
#include <QMap>

//! Size handle on top of RectangleView represented as small circle or small rectangle.
//! Placed either in corners on in the middle of the edge.

class BA_CORE_API_ SizeHandleElement : public IMaskView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::SIZEHANDLE };
    int type() const { return TYPE; }

    enum EHandleLocation
    {
        NONE,
        TOPLEFT,     TOPMIDDLE,   TOPRIGHT,
        MIDDLELEFT,               MIDDLERIGHT,
        BOTTOMRIGHT, BOTTOMMIDLE, BOTTOMLEFT,
    };

    enum EHandleType
    {
        RESIZE, RESIZE_WIDTH, RESIZE_HEIGHT
    };

    SizeHandleElement(EHandleLocation pointType, IMaskView *parent);

    QRectF boundingRect() const;

    void updateHandleElementPosition(const QRectF &rect);

    EHandleLocation getHandleLocation() const;
    EHandleLocation getOppositeHandleLocation() const;
    EHandleType getHandleType() const;

public slots:
    virtual void update_view();

signals:
    void resize_request(bool going_to_resize);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    EHandleLocation m_handleLocation;
    EHandleType m_handleType;
    static QMap<EHandleLocation, Qt::CursorShape> m_cursors;
    static QMap<EHandleLocation, EHandleType> m_location_to_type;
    static QMap<EHandleLocation, EHandleLocation> m_opposite_handle_location;
};

#endif
