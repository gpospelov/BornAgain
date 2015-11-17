// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/PolygonView.h
//! @brief     Defines PolygonView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef POLYGONVIEW_H
#define POLYGONVIEW_H

#include "IMaskView.h"
#include <QPolygonF>

//! This is a View of polygon mask (represented by PolygonItem) on GraphicsScene.

class BA_CORE_API_ PolygonView : public IMaskView
{
    Q_OBJECT

public:
    int type() const { return DesignerHelper::POLYGON; }

    PolygonView();

    void addView(IMaskView *childView, int row);

    bool isClosedPolygon();

    //! returns last added poligon point in scene coordinates
    QPointF getLastAddedPoint() const;

public slots:
//    virtual void onPropertyChange(const QString &propertyName);
    virtual void onChangedX();
    virtual void onChangedY();
    void onClosePolygonRequest(bool value);


//protected slots:
//    void onChilderChanged();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    void update_view();
    void update_polygon();
    void update_points();
    void setChildrenVisible(bool value);

    bool makePolygonClosed();

//    void update_bounding_rect();

    QPolygonF m_polygon;
    bool m_block_on_point_update;
    bool m_closed_polygon;
    bool m_close_polygon_request;
};


#endif
