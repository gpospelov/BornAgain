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

XRotationItem::XRotationItem()
    : RotationItem(Constants::XRotationType)
{
    addProperty(P_ANGLE, 0.0);
}

IRotation *XRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getChildValue(P_ANGLE).toDouble() );
    return new RotationX(alpha);
}

/* ------------------------------------------------ */

const QString YRotationItem::P_ANGLE = "Angle";

YRotationItem::YRotationItem()
    : RotationItem(Constants::YRotationType)
{
    addProperty(P_ANGLE, 0.0);
}

IRotation *YRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getChildValue(P_ANGLE).toDouble() );
    return new RotationY(alpha);
}

/* ------------------------------------------------ */

const QString ZRotationItem::P_ANGLE = "Angle";

ZRotationItem::ZRotationItem()
    : RotationItem(Constants::ZRotationType)
{
    addProperty(P_ANGLE, 0.0);
}

IRotation *ZRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getChildValue(P_ANGLE).toDouble() );
    return new RotationZ(alpha);
}

/* ------------------------------------------------ */

const QString EulerRotationItem::P_ALPHA = "Alpha";
const QString EulerRotationItem::P_BETA = "Beta";
const QString EulerRotationItem::P_GAMMA = "Gamma";

EulerRotationItem::EulerRotationItem()
    : RotationItem(Constants::EulerRotationType)
{
    addProperty(P_ALPHA, 0.0);
    addProperty(P_BETA, 0.0);
    addProperty(P_GAMMA, 0.0);
}

IRotation *EulerRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getChildValue(P_ALPHA).toDouble() );
    double beta = Units::deg2rad(getChildValue(P_BETA).toDouble() );
    double gamma = Units::deg2rad(getChildValue(P_GAMMA).toDouble() );
    return new RotationEuler(alpha, beta, gamma);
}
