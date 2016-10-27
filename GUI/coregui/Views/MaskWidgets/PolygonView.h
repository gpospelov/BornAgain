// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/PolygonView.h
//! @brief     Defines PolygonView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
    int type() const { return MaskEditorHelper::POLYGON; }

    PolygonView();

    void addView(IMaskView *childView, int row);
    bool isClosedPolygon();
    QPointF getLastAddedPoint() const;

public slots:
    bool closePolygonIfNecessary();
    void onClosePolygonRequest(bool value);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    void update_view();
    void update_polygon();
    void update_points();
    void setChildrenVisible(bool value);
    bool makePolygonClosed();

    QPolygonF m_polygon;
    bool m_block_on_point_update;
    bool m_close_polygon_request;
};

#endif // POLYGONVIEW_H
