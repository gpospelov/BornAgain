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
#include "Rectangle.h"
#include "Polygon.h"
#include "Line.h"
#include "Ellipse.h"
#include "InfinitePlane.h"
#include "Units.h"


MaskContainerItem::MaskContainerItem()
    : ParameterizedItem(Constants::MaskContainerType)
{
    addToValidChildren(Constants::RectangleMaskType);
    addToValidChildren(Constants::PolygonMaskType);
    addToValidChildren(Constants::EllipseMaskType);
    addToValidChildren(Constants::VerticalLineMaskType);
    addToValidChildren(Constants::HorizontalLineMaskType);
    addToValidChildren(Constants::MaskAllType);
}

/* ------------------------------------------------------------------------- */

const QString MaskItem::P_MASK_VALUE = "Mask value";

MaskItem::MaskItem(const QString &name)
    : ParameterizedItem(name)
{
    registerProperty(P_MASK_VALUE, true);
}


/* ------------------------------------------------------------------------- */
const QString RectangleItem::P_XLOW = "xlow";
const QString RectangleItem::P_YLOW = "ylow";
const QString RectangleItem::P_XUP = "xup";
const QString RectangleItem::P_YUP = "yup";

RectangleItem::RectangleItem()
    : MaskItem(Constants::RectangleMaskType)
{
    registerProperty(P_XLOW, 0.0).limitless();
    registerProperty(P_YLOW, 0.0).limitless();
    registerProperty(P_XUP, 0.0).limitless();
    registerProperty(P_YUP, 0.0).limitless();
}

Geometry::IShape2D *RectangleItem::createShape(double scale) const
{
    double xlow = scale*getRegisteredProperty(P_XLOW).toDouble();
    double ylow = scale*getRegisteredProperty(P_YLOW).toDouble();
    double xup = scale*getRegisteredProperty(P_XUP).toDouble();
    double yup = scale*getRegisteredProperty(P_YUP).toDouble();
    return new Geometry::Rectangle(xlow, ylow, xup, yup);
}

/* ------------------------------------------------------------------------- */
const QString PolygonPointItem::P_POSX = "X position";
const QString PolygonPointItem::P_POSY = "Y position";

PolygonPointItem::PolygonPointItem()
    : ParameterizedItem(Constants::PolygonPointType)
{
    registerProperty(P_POSX, 0.0).limitless();
    registerProperty(P_POSY, 0.0).limitless();
}

/* ------------------------------------------------------------------------- */

const QString PolygonItem::P_ISCLOSED = "Is closed";

PolygonItem::PolygonItem()
    : MaskItem(Constants::PolygonMaskType)
{
    addToValidChildren(Constants::PolygonPointType);
    registerProperty(P_ISCLOSED, false).setHidden();
}

Geometry::IShape2D *PolygonItem::createShape(double scale) const
{
    std::vector<double> x,y;
    foreach(ParameterizedItem *item, this->getChildrenOfType(Constants::PolygonPointType)) {
        x.push_back(scale*item->getRegisteredProperty(PolygonPointItem::P_POSX).toDouble());
        y.push_back(scale*item->getRegisteredProperty(PolygonPointItem::P_POSY).toDouble());
    }
    return new Geometry::Polygon(x, y);
}

/* ------------------------------------------------------------------------- */
const QString VerticalLineItem::P_POSX = "X position";

VerticalLineItem::VerticalLineItem()
    : MaskItem(Constants::VerticalLineMaskType)
{
    registerProperty(P_POSX, 0.0).limitless();
}

Geometry::IShape2D *VerticalLineItem::createShape(double scale) const
{
    return new Geometry::VerticalLine(
                scale*getRegisteredProperty(VerticalLineItem::P_POSX).toDouble());
}

/* ------------------------------------------------------------------------- */
const QString HorizontalLineItem::P_POSY = "Y position";

HorizontalLineItem::HorizontalLineItem()
    : MaskItem(Constants::HorizontalLineMaskType)
{
    registerProperty(P_POSY, 0.0).limitless();
}

Geometry::IShape2D *HorizontalLineItem::createShape(double scale) const
{
    return new Geometry::HorizontalLine(
                scale*getRegisteredProperty(HorizontalLineItem::P_POSY).toDouble());
}

/* ------------------------------------------------------------------------- */

const QString EllipseItem::P_XCENTER = "X position";
const QString EllipseItem::P_YCENTER = "Y position";
const QString EllipseItem::P_XRADIUS = "X radius";
const QString EllipseItem::P_YRADIUS = "Y radius";
const QString EllipseItem::P_ANGLE = "Angle";

EllipseItem::EllipseItem()
    : MaskItem(Constants::EllipseMaskType)
{
    registerProperty(P_XCENTER, 0.0).limitless();
    registerProperty(P_YCENTER, 0.0).limitless();
    registerProperty(P_XRADIUS, 0.0);
    registerProperty(P_YRADIUS, 0.0);
    registerProperty(P_ANGLE, 0.0).limitless();
}

Geometry::IShape2D *EllipseItem::createShape(double scale) const
{
    double xcenter = scale*getRegisteredProperty(EllipseItem::P_XCENTER).toDouble();
    double ycenter = scale*getRegisteredProperty(EllipseItem::P_YCENTER).toDouble();
    double xradius = scale*getRegisteredProperty(EllipseItem::P_XRADIUS).toDouble();
    double yradius = scale*getRegisteredProperty(EllipseItem::P_YRADIUS).toDouble();
    double angle = scale*getRegisteredProperty(EllipseItem::P_ANGLE).toDouble();

    return new Geometry::Ellipse(xcenter, ycenter, xradius, yradius, angle);
}

/* ------------------------------------------------------------------------- */

MaskAllItem::MaskAllItem()
    : MaskItem(Constants::MaskAllType)
{
    getPropertyAttribute(MaskItem::P_MASK_VALUE).setDisabled();
}

Geometry::IShape2D *MaskAllItem::createShape(double scale) const
{
    Q_UNUSED(scale);
    return new Geometry::InfinitePlane();
}
