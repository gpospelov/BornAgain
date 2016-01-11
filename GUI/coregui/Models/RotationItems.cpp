// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/RotationItems.cpp
//! @brief     Implements class RotationItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RotationItems.h"
#include "Units.h"
#include "BornAgainNamespace.h"

/* ------------------------------------------------ */

const QString XRotationItem::P_ANGLE = "Angle";

XRotationItem::XRotationItem(ParameterizedItem *parent)
    : RotationItem(Constants::XRotationType, parent)
{
    registerProperty(P_ANGLE, 0.0);
}

IRotation *XRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getRegisteredProperty(P_ANGLE).toDouble() );
    return new RotationX(alpha);
}

/* ------------------------------------------------ */

const QString YRotationItem::P_ANGLE = "Angle";

YRotationItem::YRotationItem(ParameterizedItem *parent)
    : RotationItem(Constants::YRotationType, parent)
{
    registerProperty(P_ANGLE, 0.0);
}

IRotation *YRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getRegisteredProperty(P_ANGLE).toDouble() );
    return new RotationY(alpha);
}

/* ------------------------------------------------ */

const QString ZRotationItem::P_ANGLE = "Angle";

ZRotationItem::ZRotationItem(ParameterizedItem *parent)
    : RotationItem(Constants::ZRotationType, parent)
{
    registerProperty(P_ANGLE, 0.0);
}

IRotation *ZRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getRegisteredProperty(P_ANGLE).toDouble() );
    return new RotationZ(alpha);
}

/* ------------------------------------------------ */

const QString EulerRotationItem::P_ALPHA = "Alpha";
const QString EulerRotationItem::P_BETA = "Beta";
const QString EulerRotationItem::P_GAMMA = "Gamma";

EulerRotationItem::EulerRotationItem(ParameterizedItem *parent)
    : RotationItem(Constants::EulerRotationType, parent)
{
    registerProperty(P_ALPHA, 0.0);
    registerProperty(P_BETA, 0.0);
    registerProperty(P_GAMMA, 0.0);
}

IRotation *EulerRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getRegisteredProperty(P_ALPHA).toDouble() );
    double beta = Units::deg2rad(getRegisteredProperty(P_BETA).toDouble() );
    double gamma = Units::deg2rad(getRegisteredProperty(P_GAMMA).toDouble() );
    return new RotationEuler(alpha, beta, gamma);
}
