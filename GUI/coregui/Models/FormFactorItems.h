// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/FormFactorItems.h
//! @brief     Defines FormFactorItem classes.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORITEMS_H
#define FORMFACTORITEMS_H

#include "ParameterizedItem.h"


class AnisoPyramidItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit AnisoPyramidItem(ParameterizedItem *parent=0);
    ~AnisoPyramidItem(){}
};


class BoxItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit BoxItem(ParameterizedItem *parent=0);
    ~BoxItem(){}
};


class ConeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit ConeItem(ParameterizedItem *parent=0);
    ~ConeItem(){}
};


class Cone6Item : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit Cone6Item(ParameterizedItem *parent=0);
    ~Cone6Item(){}
};


class CuboctahedronItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit CuboctahedronItem(ParameterizedItem *parent=0);
    ~CuboctahedronItem(){}
};


class CylinderItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit CylinderItem(ParameterizedItem *parent=0);
    ~CylinderItem(){}
};


class EllipsoidalCylinderItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit EllipsoidalCylinderItem(ParameterizedItem *parent=0);
    ~EllipsoidalCylinderItem(){}
};


class FullSphereItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit FullSphereItem(ParameterizedItem *parent=0);
    ~FullSphereItem(){}
};


class FullSpheroidItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit FullSpheroidItem(ParameterizedItem *parent=0);
    ~FullSpheroidItem(){}
};


class HemiEllipsoidItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit HemiEllipsoidItem(ParameterizedItem *parent=0);
    ~HemiEllipsoidItem(){}
};


class Prism3Item : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit Prism3Item(ParameterizedItem *parent=0);
    ~Prism3Item(){}
};


class Prism6Item : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit Prism6Item(ParameterizedItem *parent=0);
    ~Prism6Item(){}
};


class PyramidItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit PyramidItem(ParameterizedItem *parent=0);
    ~PyramidItem(){}
};


class Ripple1Item : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit Ripple1Item(ParameterizedItem *parent=0);
    ~Ripple1Item(){}
};


class Ripple2Item : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit Ripple2Item(ParameterizedItem *parent=0);
    ~Ripple2Item(){}
};


class TetrahedronItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit TetrahedronItem(ParameterizedItem *parent=0);
    ~TetrahedronItem(){}
};


class TruncatedSphereItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit TruncatedSphereItem(ParameterizedItem *parent=0);
    ~TruncatedSphereItem(){}
};


class TruncatedSpheroidItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit TruncatedSpheroidItem(ParameterizedItem *parent=0);
    ~TruncatedSpheroidItem(){}
};


#endif // FORMFACTORITEMS_H

