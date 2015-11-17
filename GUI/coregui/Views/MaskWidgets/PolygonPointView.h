// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/PolygonPointView.h
//! @brief     Defines PolygonPointView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef POLYGONPOINTVIEW_H
#define POLYGONPOINTVIEW_H

#include "IMaskView.h"

//! This is a View of polygon point for PolygonMaskItem

class BA_CORE_API_ PolygonPointView : public IMaskView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::POLYGONPOINT };
    int type() const { return TYPE; }

    PolygonPointView();

    QRectF boundingRect() const;

    void updateParameterizedItem(const QPointF &pos);

//    void setFirstPolygonPointFlag(bool value);

signals:
    void closePolygonRequest(bool);

public slots:
    virtual void onChangedX();
    virtual void onChangedY();
//    virtual void onPropertyChange(const QString &propertyName);
    virtual void update_view();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);


private:
    void update_position();

//    bool m_block_on_property_change;
    bool m_on_hover;
//    bool m_first_polygon_point;
};


#endif
