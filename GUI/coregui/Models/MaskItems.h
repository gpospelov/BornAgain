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

#include "ParameterizedItem.h"

namespace Geometry {
class IShape2D;
}

//! Container holding various masks as children

class BA_CORE_API_ MaskContainerItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit MaskContainerItem(ParameterizedItem *parent = 0);
};


//! A base class for all mask items
//!
class BA_CORE_API_ MaskItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_MASK_VALUE;
    explicit MaskItem(const QString &name, ParameterizedItem *parent);
    virtual Geometry::IShape2D *createShape() const { return 0;}
};

class BA_CORE_API_ RectangleItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_XLOW;
    static const QString P_YLOW;
    static const QString P_XUP;
    static const QString P_YUP;
    explicit RectangleItem(ParameterizedItem *parent=0);
    virtual Geometry::IShape2D *createShape() const;
};

class BA_CORE_API_ PolygonPointItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_POSX;
    static const QString P_POSY;

    explicit PolygonPointItem(ParameterizedItem *parent=0);

};

class BA_CORE_API_ PolygonItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_ISCLOSED;
    explicit PolygonItem(ParameterizedItem *parent=0);
    virtual Geometry::IShape2D *createShape() const;
};

class BA_CORE_API_ VerticalLineItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_POSX;
    explicit VerticalLineItem(ParameterizedItem *parent=0);
    virtual Geometry::IShape2D *createShape() const;
};

class BA_CORE_API_ HorizontalLineItem : public MaskItem
{
    Q_OBJECT
public:
    static const QString P_POSY;
    explicit HorizontalLineItem(ParameterizedItem *parent=0);
    virtual Geometry::IShape2D *createShape() const;
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
    explicit EllipseItem(ParameterizedItem *parent=0);
    virtual Geometry::IShape2D *createShape() const;
};

class BA_CORE_API_ MaskAllItem : public MaskItem
{
    Q_OBJECT
public:
    explicit MaskAllItem(ParameterizedItem *parent=0);
    virtual Geometry::IShape2D *createShape() const;
};


#endif
