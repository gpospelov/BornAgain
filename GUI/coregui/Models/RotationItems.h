// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RotationItems.h
//! @brief     Defines class RotationItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROTATIONITEMS_H
#define ROTATIONITEMS_H

#include "ParameterizedItem.h"
#include "Transform3D.h"

class RotationItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit RotationItem(const QString name, ParameterizedItem *parent) : ParameterizedItem(name, parent){}
    virtual Geometry::Transform3D *createTransform() const{ return 0;}
    virtual ~RotationItem(){}
};


class XRotationItem : public RotationItem
{
    Q_OBJECT
public:
    static const QString P_ANGLE;
    explicit XRotationItem(ParameterizedItem *parent=0);
    Geometry::Transform3D *createTransform() const;
};

class YRotationItem : public RotationItem
{
    Q_OBJECT
public:
    static const QString P_ANGLE;
    explicit YRotationItem(ParameterizedItem *parent=0);
    Geometry::Transform3D *createTransform() const;
};

class ZRotationItem : public RotationItem
{
    Q_OBJECT
public:
    static const QString P_ANGLE;
    explicit ZRotationItem(ParameterizedItem *parent=0);
    Geometry::Transform3D *createTransform() const;
};

class EulerRotationItem : public RotationItem
{
    Q_OBJECT
public:
    static const QString P_ALPHA, P_BETA, P_GAMMA;
    explicit EulerRotationItem(ParameterizedItem *parent=0);
    Geometry::Transform3D *createTransform() const;
};

#endif // ROTATIONITEMS_H

