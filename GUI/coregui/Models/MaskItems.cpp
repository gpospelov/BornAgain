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


MaskContainerItem::MaskContainerItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::MaskContainerType, parent)
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

RectangleItem::RectangleItem(ParameterizedItem *parent)
    : MaskItem(Constants::RectangleMaskType, parent)
{
    setItemName(QStringLiteral("Rectangle"));
    registerProperty(P_POSX, 0.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_POSY, 0.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
}

Geometry::IShape2D *RectangleItem::createShape() const
{
    double xlow = getRegisteredProperty(P_POSX).toDouble();
    double ylow = getRegisteredProperty(P_POSY).toDouble() - getRegisteredProperty(P_HEIGHT).toDouble();
    double xup = getRegisteredProperty(P_POSX).toDouble() + getRegisteredProperty(P_WIDTH).toDouble();
    double yup = getRegisteredProperty(P_POSY).toDouble();
    return new Geometry::Rectangle(Units::deg2rad(xlow), Units::deg2rad(ylow), Units::deg2rad(xup), Units::deg2rad(yup));
}

/* ------------------------------------------------------------------------- */
const QString PolygonPointItem::P_POSX = "X position";
const QString PolygonPointItem::P_POSY = "Y position";

PolygonPointItem::PolygonPointItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::PolygonPointType, parent)
{
    setItemName(QStringLiteral("Point"));
    registerProperty(P_POSX, 0.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_POSY, 0.0, PropertyAttribute(AttLimits::limitless()));
}


/* ------------------------------------------------------------------------- */

const QString PolygonItem::P_ISCLOSED = "Is closed";

PolygonItem::PolygonItem(ParameterizedItem *parent)
    : MaskItem(Constants::PolygonMaskType, parent)
{
    setItemName(QStringLiteral("Polygon"));
    addToValidChildren(Constants::PolygonPointType);
    registerProperty(P_ISCLOSED, false, PropertyAttribute::hiddenProperty());
}

Geometry::IShape2D *PolygonItem::createShape() const
{
    std::vector<double> x,y;
    foreach(ParameterizedItem *item, this->childItems()) {
        x.push_back(Units::deg2rad(item->getRegisteredProperty(PolygonPointItem::P_POSX).toDouble()));
        y.push_back(Units::deg2rad(item->getRegisteredProperty(PolygonPointItem::P_POSY).toDouble()));
    }
    return new Geometry::Polygon(x, y);
}


/* ------------------------------------------------------------------------- */
const QString VerticalLineItem::P_POSX = "X position";

VerticalLineItem::VerticalLineItem(ParameterizedItem *parent)
    : MaskItem(Constants::VerticalLineMaskType, parent)
{
    setItemName(QStringLiteral("VerticalLine"));
    registerProperty(P_POSX, 0.0, PropertyAttribute(AttLimits::limitless()));
}

Geometry::IShape2D *VerticalLineItem::createShape() const
{
    return new Geometry::VerticalLine(
                Units::deg2rad(getRegisteredProperty(VerticalLineItem::P_POSX).toDouble()));
}

/* ------------------------------------------------------------------------- */
const QString HorizontalLineItem::P_POSY = "Y position";

HorizontalLineItem::HorizontalLineItem(ParameterizedItem *parent)
    : MaskItem(Constants::HorizontalLineMaskType, parent)
{
    setItemName(QStringLiteral("HorizontalLine"));
    registerProperty(P_POSY, 0.0, PropertyAttribute(AttLimits::limitless()));
}

Geometry::IShape2D *HorizontalLineItem::createShape() const
{
    return new Geometry::HorizontalLine(
                Units::deg2rad(getRegisteredProperty(HorizontalLineItem::P_POSY).toDouble()));
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
    registerProperty(P_POSX, 0.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_POSY, 0.0, PropertyAttribute(AttLimits::limitless()));
    registerProperty(P_WIDTH, 0.0);
    registerProperty(P_HEIGHT, 0.0);
    registerProperty(P_ANGLE, 0.0, PropertyAttribute(AttLimits::limitless()));
}

Geometry::IShape2D *EllipseItem::createShape() const
{
    double xcenter = Units::deg2rad(getRegisteredProperty(EllipseItem::P_POSX).toDouble());
    double ycenter = Units::deg2rad(getRegisteredProperty(EllipseItem::P_POSY).toDouble());
    double xradius = Units::deg2rad(getRegisteredProperty(EllipseItem::P_WIDTH).toDouble()/2.);
    double yradius = Units::deg2rad(getRegisteredProperty(EllipseItem::P_HEIGHT).toDouble()/2.);
    double angle = Units::deg2rad(getRegisteredProperty(EllipseItem::P_ANGLE).toDouble());

    return new Geometry::Ellipse(xcenter, ycenter, xradius, yradius, angle);
}

/* ------------------------------------------------------------------------- */

MaskAllItem::MaskAllItem(ParameterizedItem *parent)
    : MaskItem(Constants::MaskAllType, parent)
{
    setItemName(QStringLiteral("MaskAllPlane"));
    setPropertyAppearance(MaskItem::P_MASK_VALUE, PropertyAttribute::DISABLED);
}

Geometry::IShape2D *MaskAllItem::createShape() const
{
    return new Geometry::InfinitePlane();
}

