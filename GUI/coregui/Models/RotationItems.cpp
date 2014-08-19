// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/ParticleItem.cpp
//! @brief     Implements class ParticleItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RotationItems.h"
#include "Units.h"

/* ------------------------------------------------ */

const QString XRotationItem::P_ANGLE = "Angle";

XRotationItem::XRotationItem(ParameterizedItem *parent)
    : RotationItem(Constants::XRotationType, parent)
{
    setItemName(Constants::XRotationType);
    registerProperty(P_ANGLE, 0.0);
}

Geometry::Transform3D *XRotationItem::createTransform() const
{
    double alpha = Units::deg2rad(getRegisteredProperty(P_ANGLE).toDouble() );
    return new Geometry::Transform3D(
                Geometry::Transform3D::createRotateX(alpha) );
}

/* ------------------------------------------------ */

const QString YRotationItem::P_ANGLE = "Angle";

YRotationItem::YRotationItem(ParameterizedItem *parent)
    : RotationItem(Constants::YRotationType, parent)
{
    setItemName(Constants::YRotationType);
    registerProperty(P_ANGLE, 0.0);
}

Geometry::Transform3D *YRotationItem::createTransform() const
{
    double alpha = Units::deg2rad(getRegisteredProperty(P_ANGLE).toDouble() );
    return new Geometry::Transform3D(
                Geometry::Transform3D::createRotateY(alpha) );
}

/* ------------------------------------------------ */

const QString ZRotationItem::P_ANGLE = "Angle";

ZRotationItem::ZRotationItem(ParameterizedItem *parent)
    : RotationItem(Constants::ZRotationType, parent)
{
    setItemName(Constants::ZRotationType);
    registerProperty(P_ANGLE, 0.0);
}

Geometry::Transform3D *ZRotationItem::createTransform() const
{
    double alpha = Units::deg2rad(getRegisteredProperty(P_ANGLE).toDouble() );
    return new Geometry::Transform3D(
                Geometry::Transform3D::createRotateZ(alpha) );
}

/* ------------------------------------------------ */

const QString EulerRotationItem::P_ALPHA = "Alpha";
const QString EulerRotationItem::P_BETA = "Beta";
const QString EulerRotationItem::P_GAMMA = "Gamma";

EulerRotationItem::EulerRotationItem(ParameterizedItem *parent)
    : RotationItem(Constants::EulerRotationType, parent)
{
    setItemName(Constants::EulerRotationType);
    registerProperty(P_ALPHA, 0.0);
    registerProperty(P_BETA, 0.0);
    registerProperty(P_GAMMA, 0.0);
}

Geometry::Transform3D *EulerRotationItem::createTransform() const
{
    double alpha = Units::deg2rad(getRegisteredProperty(P_ALPHA).toDouble() );
    double beta = Units::deg2rad(getRegisteredProperty(P_BETA).toDouble() );
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble() );
    return new Geometry::Transform3D(
                Geometry::Transform3D::createRotateEuler(
                    alpha, beta, gamma) );
}

/* ------------------------------------------------ */

