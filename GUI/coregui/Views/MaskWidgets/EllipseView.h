// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/EllipseView.h
//! @brief     Defines EllipseView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ELLIPSEVIEW_H
#define ELLIPSEVIEW_H

#include "RectangleBaseView.h"

//! This is a View of ellipse mask (represented by EllipseItem) on GraphicsScene.
//! Given view follows standard QGraphicsScene notations: (x,y) is top left corner.

class BA_CORE_API_ EllipseView : public RectangleBaseView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::ELLIPSE; }

    EllipseView();

public slots:
    virtual void onChangedX();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString &propertyName);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    void update_position();
    QRectF mask_rectangle();
    qreal left() const;
    qreal right() const;
    qreal top() const;
    qreal bottom() const;
};

#endif // ELLIPSEVIEW_H
