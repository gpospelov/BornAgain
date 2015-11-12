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
    PolygonView();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    void update_view();
    void update_polygon();
//    void update_bounding_rect();

    QPolygonF m_polygon;
};


#endif
