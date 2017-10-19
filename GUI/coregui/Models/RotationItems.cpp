// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RotationItems.cpp
//! @brief     Implements class RotationItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RotationItems.h"
#include "Units.h"
#include "Rotations.h"

// ----------------------------------------------------------------------------

const QString XRotationItem::P_ANGLE = "Angle";

XRotationItem::XRotationItem()
    : RotationItem(Constants::XRotationType)
{
    setToolTip(QStringLiteral("Particle rotation around x-axis"));
    addProperty(P_ANGLE, 0.0)->setToolTip(
        QStringLiteral("Rotation angle around x-axis in degrees"));
}

std::unique_ptr<IRotation> XRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getItemValue(P_ANGLE).toDouble());
    return std::make_unique<RotationX>(alpha);
}

// ----------------------------------------------------------------------------

const QString YRotationItem::P_ANGLE = "Angle";

YRotationItem::YRotationItem()
    : RotationItem(Constants::YRotationType)
{
    setToolTip(QStringLiteral("Particle rotation around y-axis"));
    addProperty(P_ANGLE, 0.0)->setToolTip(
        QStringLiteral("Rotation angle around y-axis in degrees"));
}

std::unique_ptr<IRotation> YRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getItemValue(P_ANGLE).toDouble() );
    return std::make_unique<RotationY>(alpha);
}

// ----------------------------------------------------------------------------

const QString ZRotationItem::P_ANGLE = "Angle";

ZRotationItem::ZRotationItem()
    : RotationItem(Constants::ZRotationType)
{
    setToolTip(QStringLiteral("Particle rotation around z-axis"));
    addProperty(P_ANGLE, 0.0)->setToolTip(
        QStringLiteral("Rotation angle around z-axis in degrees"));
}

std::unique_ptr<IRotation> ZRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getItemValue(P_ANGLE).toDouble() );
    return std::make_unique<RotationZ>(alpha);
}

// ----------------------------------------------------------------------------

const QString EulerRotationItem::P_ALPHA = "Alpha";
const QString EulerRotationItem::P_BETA = "Beta";
const QString EulerRotationItem::P_GAMMA = "Gamma";

EulerRotationItem::EulerRotationItem()
    : RotationItem(Constants::EulerRotationType)
{
    setToolTip(QStringLiteral("Sequence of three rotations following Euler angles \n"
                              "notation z-x'-z'"));
    addProperty(P_ALPHA, 0.0)->setToolTip(
        QStringLiteral("First Euler anle in z-x'-z' sequence in degrees"));
    addProperty(P_BETA, 0.0)->setToolTip(
        QStringLiteral("Second Euler anle in z-x'-z' sequence in degrees"));
    addProperty(P_GAMMA, 0.0)->setToolTip(
        QStringLiteral("Third Euler anle in z-x'-z' sequence in degrees"));
}

std::unique_ptr<IRotation> EulerRotationItem::createRotation() const
{
    double alpha = Units::deg2rad(getItemValue(P_ALPHA).toDouble() );
    double beta = Units::deg2rad(getItemValue(P_BETA).toDouble() );
    double gamma = Units::deg2rad(getItemValue(P_GAMMA).toDouble() );
    return std::make_unique<RotationEuler>(alpha, beta, gamma);
}
