// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FormFactorItems.cpp
//! @brief     Implements FormFactorItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorItems.h"
#include "FormFactors.h"
#include "Units.h"
#include "GUIHelpers.h"
#include "BornAgainNamespace.h"

/* ------------------------------------------------ */

const QString AnisoPyramidItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString AnisoPyramidItem::P_WIDTH = QString::fromStdString(BornAgain::Width);
const QString AnisoPyramidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString AnisoPyramidItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

AnisoPyramidItem::AnisoPyramidItem()
    : FormFactorItem(Constants::AnisoPyramidType)
{
    registerProperty(P_LENGTH, 20.0);
    registerProperty(P_WIDTH, 16.0);
    registerProperty(P_HEIGHT, 13.0);
    registerProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> AnisoPyramidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorAnisoPyramid>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_WIDTH).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble(),
                getRegisteredProperty(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString BoxItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString BoxItem::P_WIDTH = QString::fromStdString(BornAgain::Width);
const QString BoxItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

BoxItem::BoxItem()
    : FormFactorItem(Constants::BoxType)
{
    registerProperty(P_LENGTH, 20.0);
    registerProperty(P_WIDTH, 16.0);
    registerProperty(P_HEIGHT, 13.0);
}

std::unique_ptr<IFormFactor> BoxItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorBox>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_WIDTH).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString ConeItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString ConeItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString ConeItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

ConeItem::ConeItem()
    : FormFactorItem(Constants::ConeType)
{
    registerProperty(P_RADIUS, 10.0);
    registerProperty(P_HEIGHT, 13.0);
    registerProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> ConeItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorCone>(
                getRegisteredProperty(P_RADIUS).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble(),
                getRegisteredProperty(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString Cone6Item::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString Cone6Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString Cone6Item::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

Cone6Item::Cone6Item()
    : FormFactorItem(Constants::Cone6Type)
{
    registerProperty(P_RADIUS, 10.0);
    registerProperty(P_HEIGHT, 13.0);
    registerProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> Cone6Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorCone6>(
                getRegisteredProperty(P_RADIUS).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble(),
                getRegisteredProperty(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString CuboctahedronItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString CuboctahedronItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString CuboctahedronItem::P_HEIGHT_RATIO = QString::fromStdString(BornAgain::HeightRatio);
const QString CuboctahedronItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

CuboctahedronItem::CuboctahedronItem()
    : FormFactorItem(Constants::CuboctahedronType)
{
    registerProperty(P_LENGTH, 20.0);
    registerProperty(P_HEIGHT, 13.0);
    registerProperty(P_HEIGHT_RATIO, 0.7);//.lowerLimited(0.0);
    registerProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> CuboctahedronItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorCuboctahedron>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble(),
                getRegisteredProperty(P_HEIGHT_RATIO).toDouble(),
                getRegisteredProperty(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString CylinderItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString CylinderItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

CylinderItem::CylinderItem()
    : FormFactorItem(Constants::CylinderType)
{
    registerProperty(P_RADIUS, 8.0);
    registerProperty(P_HEIGHT, 16.0);
}

std::unique_ptr<IFormFactor> CylinderItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorCylinder>(
                getRegisteredProperty(P_RADIUS).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString EllipsoidalCylinderItem::P_RADIUS_X = QString::fromStdString(BornAgain::RadiusX);
const QString EllipsoidalCylinderItem::P_RADIUS_Y = QString::fromStdString(BornAgain::RadiusY);
const QString EllipsoidalCylinderItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

EllipsoidalCylinderItem::EllipsoidalCylinderItem()
    : FormFactorItem(Constants::EllipsoidalCylinderType)
{
    registerProperty(P_RADIUS_X, 8.0);
    registerProperty(P_RADIUS_Y, 13.0);
    registerProperty(P_HEIGHT, 16.0);
}

std::unique_ptr<IFormFactor> EllipsoidalCylinderItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorEllipsoidalCylinder>(
                getRegisteredProperty(P_RADIUS_X).toDouble(),
                getRegisteredProperty(P_RADIUS_Y).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString FullSphereItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);

FullSphereItem::FullSphereItem()
    : FormFactorItem(Constants::FullSphereType)
{
    registerProperty(P_RADIUS, 8.0);
}

std::unique_ptr<IFormFactor> FullSphereItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorFullSphere>(
                getRegisteredProperty(P_RADIUS).toDouble()
                );
}

/* ------------------------------------------------ */

const QString FullSpheroidItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString FullSpheroidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

FullSpheroidItem::FullSpheroidItem()
    : FormFactorItem(Constants::FullSpheroidType)
{
    registerProperty(P_RADIUS, 10.0);
    registerProperty(P_HEIGHT, 13.0);
}

std::unique_ptr<IFormFactor> FullSpheroidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorFullSpheroid>(
                getRegisteredProperty(P_RADIUS).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString HemiEllipsoidItem::P_RADIUS_X = QString::fromStdString(BornAgain::RadiusX);
const QString HemiEllipsoidItem::P_RADIUS_Y = QString::fromStdString(BornAgain::RadiusY);
const QString HemiEllipsoidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

HemiEllipsoidItem::HemiEllipsoidItem()
    : FormFactorItem(Constants::HemiEllipsoidType)
{
    registerProperty(P_RADIUS_X, 10.0);
    registerProperty(P_RADIUS_Y, 6.0);
    registerProperty(P_HEIGHT, 8.0);
}

std::unique_ptr<IFormFactor> HemiEllipsoidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorHemiEllipsoid>(
                getRegisteredProperty(P_RADIUS_X).toDouble(),
                getRegisteredProperty(P_RADIUS_Y).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString Prism3Item::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString Prism3Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);

Prism3Item::Prism3Item()
    : FormFactorItem(Constants::Prism3Type)
{
    registerProperty(P_LENGTH, 10.0);
    registerProperty(P_HEIGHT, 13.0);
}

std::unique_ptr<IFormFactor> Prism3Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorPrism3>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString Prism6Item::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString Prism6Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);

Prism6Item::Prism6Item()
    : FormFactorItem(Constants::Prism6Type)
{
    registerProperty(P_RADIUS, 5.0);
    registerProperty(P_HEIGHT, 11.0);
}

std::unique_ptr<IFormFactor> Prism6Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorPrism6>(
                getRegisteredProperty(P_RADIUS).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString PyramidItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString PyramidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString PyramidItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

PyramidItem::PyramidItem()
    : FormFactorItem(Constants::PyramidType)
{
    registerProperty(P_LENGTH, 18.0);
    registerProperty(P_HEIGHT, 13.0);
    registerProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> PyramidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorPyramid>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble(),
                getRegisteredProperty(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString Ripple1Item::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString Ripple1Item::P_WIDTH = QString::fromStdString(BornAgain::Width);
const QString Ripple1Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);

Ripple1Item::Ripple1Item()
    : FormFactorItem(Constants::Ripple1Type)
{
    registerProperty(P_LENGTH, 27.0);
    registerProperty(P_WIDTH, 20.0);
    registerProperty(P_HEIGHT, 14.0);
}

std::unique_ptr<IFormFactor> Ripple1Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorRipple1>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_WIDTH).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString Ripple2Item::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString Ripple2Item::P_WIDTH = QString::fromStdString(BornAgain::Width);
const QString Ripple2Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString Ripple2Item::P_ASYMMETRY = QString::fromStdString(BornAgain::AsymmetryLength);

Ripple2Item::Ripple2Item()
    : FormFactorItem(Constants::Ripple2Type)
{
    registerProperty(P_LENGTH, 36.0);
    registerProperty(P_WIDTH, 25.0);
    registerProperty(P_HEIGHT, 14.0);
    registerProperty(P_ASYMMETRY, 3.0);
}

std::unique_ptr<IFormFactor> Ripple2Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorRipple2>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_WIDTH).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble(),
                getRegisteredProperty(P_ASYMMETRY).toDouble()
                );
}

/* ------------------------------------------------ */

const QString TetrahedronItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString TetrahedronItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString TetrahedronItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

TetrahedronItem::TetrahedronItem()
    : FormFactorItem(Constants::TetrahedronType)
{
    registerProperty(P_LENGTH, 15.0);
    registerProperty(P_HEIGHT, 6.0);
    registerProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> TetrahedronItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTetrahedron>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble(),
                getRegisteredProperty(P_ALPHA).toDouble()*Units::degree
                );
}


/* ------------------------------------------------ */

const QString TruncatedCubeItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString TruncatedCubeItem::P_REMOVED_LENGTH = QString::fromStdString(BornAgain::RemovedLength);

TruncatedCubeItem::TruncatedCubeItem()
    : FormFactorItem(Constants::TruncatedCubeType)
{
    registerProperty(P_LENGTH, 15.0);
    registerProperty(P_REMOVED_LENGTH, 6.0);
}

std::unique_ptr<IFormFactor> TruncatedCubeItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTruncatedCube>(
                getRegisteredProperty(P_LENGTH).toDouble(),
                getRegisteredProperty(P_REMOVED_LENGTH).toDouble()
                );
}

/* ------------------------------------------------ */

const QString TruncatedSphereItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString TruncatedSphereItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

TruncatedSphereItem::TruncatedSphereItem()
    : FormFactorItem(Constants::TruncatedSphereType)
{
    registerProperty(P_RADIUS, 5.0);
    registerProperty(P_HEIGHT, 7.0);
}

std::unique_ptr<IFormFactor> TruncatedSphereItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTruncatedSphere>(
                getRegisteredProperty(P_RADIUS).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString TruncatedSpheroidItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString TruncatedSpheroidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString TruncatedSpheroidItem::P_HFC = QString::fromStdString(BornAgain::HeightFlattening);

TruncatedSpheroidItem::TruncatedSpheroidItem()
    : FormFactorItem(Constants::TruncatedSpheroidType)
{
    registerProperty(P_RADIUS, 7.5);
    registerProperty(P_HEIGHT, 9.0);
    registerProperty(P_HFC, 1.2);
}

std::unique_ptr<IFormFactor> TruncatedSpheroidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTruncatedSpheroid>(
                getRegisteredProperty(P_RADIUS).toDouble(),
                getRegisteredProperty(P_HEIGHT).toDouble(),
                getRegisteredProperty(P_HFC).toDouble()
                );
}



