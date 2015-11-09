// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/IMaskView.h
//! @brief     Defines interface class IMaskView for all masks on graphics scene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTANGLEVIEW_H
#define RECTANGLEVIEW_H

#include "IMaskView.h"
#include "PointElement.h"
#include <QMap>

//! This is a View of rectangular mask ( represented by RectangleItem) on GraphicsScene.
//! Given view follows standard QGraphicsScene notations: (x,y) is top left corner.

class BA_CORE_API_ RectangleView : public IMaskView
{
    Q_OBJECT

public:
    RectangleView();

//    void setParameterizedItem(ParameterizedItem *item);

public slots:
    virtual void onChangedX();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString &propertyName);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
//    void paint_rectangle_marker(QPainter *painter, const QPointF &pos);
    void update_view();
    void update_bounding_rect();
    void update_position();    
    qreal left() const;
    qreal right() const;
    qreal width() const;
    qreal top() const;
    qreal bottom() const;
    qreal height() const;
    void create_points();
    bool m_block_on_property_change;
    QRectF m_mask_rect; // mask rectangle in scene coordinates
    QMap<PointElement::EPointType, PointElement *> m_point_elements;

};


#endif
