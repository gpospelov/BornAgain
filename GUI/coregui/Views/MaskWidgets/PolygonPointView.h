// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/PolygonPointView.h
//! @brief     Defines PolygonPointView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef POLYGONPOINTVIEW_H
#define POLYGONPOINTVIEW_H

#include "IShape2DView.h"

//! This is a View of polygon point for PolygonMaskItem

class BA_CORE_API_ PolygonPointView : public IShape2DView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::POLYGONPOINT; }

    PolygonPointView();

    QRectF boundingRect() const;

    void updateParameterizedItem(const QPointF& pos);

signals:
    void closePolygonRequest(bool);
    void propertyChanged();

protected slots:
    virtual void update_view();
    virtual void onPropertyChange(const QString&);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:
    bool m_on_hover;
};

#endif // POLYGONPOINTVIEW_H
