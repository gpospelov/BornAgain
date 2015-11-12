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
#include <QGraphicsObject>

//! This is a View of polygon point for PolygonMaskItem

class BA_CORE_API_ PolygonPointView : public QGraphicsObject
{
    Q_OBJECT

public:
    PolygonPointView();

    QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};


#endif
