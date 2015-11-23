// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MaskItems.cpp
//! @brief     Implements MaskItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskItems.h"

const QString MaskItem::P_MASK_VALUE = "Mask value";

MaskItem::MaskItem(const QString &name, ParameterizedItem *parent)
    : ParameterizedItem(name, parent)
{
    registerProperty(P_MASK_VALUE, true);
}


/* ------------------------------------------------------------------------- */
const QString RectangleItem::P_POSX = "X position";
const QString RectangleItem::P_POSY = "Y position";
const QString RectangleItem::P_WIDTH = "Width";
const QString RectangleItem::P_HEIGHT = "Height";
const QString RectangleItem::P_ANGLE = "Angle";

RectangleItem::RectangleItem(ParameterizedItem *parent)
    : MaskItem(Constants::RectangleMaskType, parent)
{
    setItemName(QStringLiteral("Rectangle"));
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
    registerProperty(P_ANGLE, 0.0);
}

/* ------------------------------------------------------------------------- */
const QString PolygonPointItem::P_POSX = "X position";
const QString PolygonPointItem::P_POSY = "Y position";

PolygonPointItem::PolygonPointItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PolygonPointType, parent)
{
    setItemName(QStringLiteral("Point"));
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
}


/* ------------------------------------------------------------------------- */

const QString PolygonItem::P_ISCLOSED = "Is closed";

PolygonItem::PolygonItem(ParameterizedItem *parent)
    : MaskItem(Constants::PolygonMaskType, parent)
{
    setItemName(QStringLiteral("Polygon"));
    addToValidChildren(Constants::PolygonPointType);
    registerProperty(P_ISCLOSED, false);
}


/* ------------------------------------------------------------------------- */
const QString VerticalLineItem::P_POSX = "X position";

VerticalLineItem::VerticalLineItem(ParameterizedItem *parent)
    : MaskItem(Constants::VerticalLineMaskType, parent)
{
    setItemName(QStringLiteral("VerticalLine"));
    registerProperty(P_POSX, 0.0);
}

/* ------------------------------------------------------------------------- */
const QString HorizontalLineItem::P_POSY = "Y position";

HorizontalLineItem::HorizontalLineItem(ParameterizedItem *parent)
    : MaskItem(Constants::HorizontalLineMaskType, parent)
{
    setItemName(QStringLiteral("HorizontalLine"));
    registerProperty(P_POSY, 0.0);
}

/* ------------------------------------------------------------------------- */

const QString EllipseItem::P_POSX = "X position";
const QString EllipseItem::P_POSY = "Y position";
const QString EllipseItem::P_WIDTH = "Width";
const QString EllipseItem::P_HEIGHT = "Height";
const QString EllipseItem::P_ANGLE = "Angle";

EllipseItem::EllipseItem(ParameterizedItem *parent)
    : MaskItem(Constants::EllipseMaskType, parent)
{
    setItemName(QStringLiteral("Ellipse"));
    registerProperty(P_POSX, 0.0);
    registerProperty(P_POSY, 0.0);
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
    registerProperty(P_ANGLE, 0.0);
}

/* ------------------------------------------------------------------------- */

MaskAllItem::MaskAllItem(ParameterizedItem *parent)
    : MaskItem(Constants::MaskAllType, parent)
{
    setItemName(QStringLiteral("MaskAllPlane"));
}
