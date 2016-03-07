// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/MaskItems.h
//! @brief     Defines MaskItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKITEMS_H
#define MASKITEMS_H

#include "SessionItem.h"
#include <memory>

namespace Geometry {
class IShape2D;
}

//! Container holding various masks as children

class BA_CORE_API_ MaskContainerItem : public SessionItem
{
    Q_OBJECT
public:
    explicit MaskContainerItem();
};


//! A base class for all mask items
//!
class BA_CORE_API_ MaskItem : public SessionItem
{
    Q_OBJECT
public:
    static const QString P_MASK_VALUE;
    explicit MaskItem(const QString &name);
    virtual std::unique_ptr<Geometry::IShape2D> createShape(double scale = 1.0) const;
};

class BA_CORE_API_ RectangleItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_XLOW;
    static const QString P_YLOW;
    static const QString P_XUP;
    static const QString P_YUP;
    explicit RectangleItem();
    virtual std::unique_ptr<Geometry::IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ PolygonPointItem : public SessionItem
{
    Q_OBJECT
public:
    static const QString P_POSX;
    static const QString P_POSY;
    explicit PolygonPointItem();
};

class BA_CORE_API_ PolygonItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_ISCLOSED;
    explicit PolygonItem();
    virtual std::unique_ptr<Geometry::IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ VerticalLineItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_POSX;
    explicit VerticalLineItem();
    virtual std::unique_ptr<Geometry::IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ HorizontalLineItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_POSY;
    explicit HorizontalLineItem();
    virtual std::unique_ptr<Geometry::IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ EllipseItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_XCENTER;
    static const QString P_YCENTER;
    static const QString P_XRADIUS;
    static const QString P_YRADIUS;
    static const QString P_ANGLE;
    explicit EllipseItem();
    virtual std::unique_ptr<Geometry::IShape2D> createShape(double scale) const;
};

class BA_CORE_API_ MaskAllItem : public MaskItem
{
    Q_OBJECT
public:
    explicit MaskAllItem();
    virtual std::unique_ptr<Geometry::IShape2D> createShape(double scale) const;
};


#endif
