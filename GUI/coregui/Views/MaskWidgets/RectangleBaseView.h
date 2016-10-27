// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/RectangleBaseView.h
//! @brief     Defines RectangleBaseView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef RECTANGLEBASEVIEW_H
#define RECTANGLEBASEVIEW_H

#include "IMaskView.h"
#include "SizeHandleElement.h"
#include <QMap>

//! Base view for all rectangular-like masks.

class BA_CORE_API_ RectangleBaseView : public IMaskView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::RECTANGLEBASE; }

    RectangleBaseView();

private slots:
    void onSizeHandleElementRequest(bool going_to_resize);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected:
    void update_view();

    virtual void update_bounding_rect();
    virtual void update_position() = 0;
    virtual QRectF mask_rectangle() = 0;
    virtual qreal left() const = 0;
    virtual qreal right() const = 0;
    virtual qreal top() const = 0;
    virtual qreal bottom() const = 0;

    qreal width() const;
    qreal height() const;

    void create_size_handle_elements();
    bool m_block_on_property_change;
    QRectF m_mask_rect; //!< mask rectangle in scene coordinates
    QMap<SizeHandleElement::EHandleLocation, SizeHandleElement *> m_resize_handles;
     //!< coordinates of corner opposite to the grip corner at the moment it first clicked
     //!< in scene coordinates
    QPointF m_resize_opposite_origin;
    SizeHandleElement *m_activeHandleElement;
};

#endif // RECTANGLEBASEVIEW_H
