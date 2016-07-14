// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FormFactorItems.cpp
//! @brief     Implements FormFactorItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FormFactorItems.h"
#include "FormFactors.h"
#include "GUIHelpers.h"

/* ------------------------------------------------ */

const QString AnisoPyramidItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString AnisoPyramidItem::P_WIDTH = QString::fromStdString(BornAgain::Width);
const QString AnisoPyramidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString AnisoPyramidItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

AnisoPyramidItem::AnisoPyramidItem()
    : FormFactorItem(Constants::AnisoPyramidType)
{
    addProperty(P_LENGTH, 20.0);
    addProperty(P_WIDTH, 16.0);
    addProperty(P_HEIGHT, 13.0);
    addProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> AnisoPyramidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorAnisoPyramid>(
                getItemValue(P_LENGTH).toDouble(),
                getItemValue(P_WIDTH).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString BoxItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString BoxItem::P_WIDTH = QString::fromStdString(BornAgain::Width);
const QString BoxItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

BoxItem::BoxItem()
    : FormFactorItem(Constants::BoxType)
{
    addProperty(P_LENGTH, 20.0);
    addProperty(P_WIDTH, 16.0);
    addProperty(P_HEIGHT, 13.0);
}

std::unique_ptr<IFormFactor> BoxItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorBox>(
                getItemValue(P_LENGTH).toDouble(),
                getItemValue(P_WIDTH).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString ConeItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString ConeItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString ConeItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

ConeItem::ConeItem()
    : FormFactorItem(Constants::ConeType)
{
    addProperty(P_RADIUS, 10.0);
    addProperty(P_HEIGHT, 13.0);
    addProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> ConeItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorCone>(
                getItemValue(P_RADIUS).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString Cone6Item::P_BASEEDGE = QString::fromStdString(BornAgain::BaseEdge);
const QString Cone6Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString Cone6Item::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

Cone6Item::Cone6Item()
    : FormFactorItem(Constants::Cone6Type)
{
    addProperty(P_BASEEDGE, 10.0);
    addProperty(P_HEIGHT, 13.0);
    addProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> Cone6Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorCone6>(
                getItemValue(P_BASEEDGE).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_ALPHA).toDouble()*Units::degree
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
    addProperty(P_LENGTH, 20.0);
    addProperty(P_HEIGHT, 13.0);
    addProperty(P_HEIGHT_RATIO, 0.7)->setLimits(AttLimits::lowerLimited(0.0));
    addProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> CuboctahedronItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorCuboctahedron>(
                getItemValue(P_LENGTH).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_HEIGHT_RATIO).toDouble(),
                getItemValue(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString CylinderItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString CylinderItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

CylinderItem::CylinderItem()
    : FormFactorItem(Constants::CylinderType)
{
    addProperty(P_RADIUS, 8.0);
    addProperty(P_HEIGHT, 16.0);
}

std::unique_ptr<IFormFactor> CylinderItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorCylinder>(
                getItemValue(P_RADIUS).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString DodecahedronItem::P_EDGE = QString::fromStdString(BornAgain::Edge);

DodecahedronItem::DodecahedronItem()
    : FormFactorItem(Constants::DodecahedronType)
{
    addProperty(P_EDGE, 10.0);
}

std::unique_ptr<IFormFactor> DodecahedronItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorDodecahedron>(
                getItemValue(P_EDGE).toDouble()
                );
}


/* ------------------------------------------------ */

const QString EllipsoidalCylinderItem::P_RADIUS_X = QString::fromStdString(BornAgain::RadiusX);
const QString EllipsoidalCylinderItem::P_RADIUS_Y = QString::fromStdString(BornAgain::RadiusY);
const QString EllipsoidalCylinderItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

EllipsoidalCylinderItem::EllipsoidalCylinderItem()
    : FormFactorItem(Constants::EllipsoidalCylinderType)
{
    addProperty(P_RADIUS_X, 8.0);
    addProperty(P_RADIUS_Y, 13.0);
    addProperty(P_HEIGHT, 16.0);
}

std::unique_ptr<IFormFactor> EllipsoidalCylinderItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorEllipsoidalCylinder>(
                getItemValue(P_RADIUS_X).toDouble(),
                getItemValue(P_RADIUS_Y).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString FullSphereItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);

FullSphereItem::FullSphereItem()
    : FormFactorItem(Constants::FullSphereType)
{
    addProperty(P_RADIUS, 8.0);
}

std::unique_ptr<IFormFactor> FullSphereItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorFullSphere>(
                getItemValue(P_RADIUS).toDouble()
                );
}

/* ------------------------------------------------ */

const QString FullSpheroidItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString FullSpheroidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

FullSpheroidItem::FullSpheroidItem()
    : FormFactorItem(Constants::FullSpheroidType)
{
    addProperty(P_RADIUS, 10.0);
    addProperty(P_HEIGHT, 13.0);
}

std::unique_ptr<IFormFactor> FullSpheroidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorFullSpheroid>(
                getItemValue(P_RADIUS).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString HemiEllipsoidItem::P_RADIUS_X = QString::fromStdString(BornAgain::RadiusX);
const QString HemiEllipsoidItem::P_RADIUS_Y = QString::fromStdString(BornAgain::RadiusY);
const QString HemiEllipsoidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

HemiEllipsoidItem::HemiEllipsoidItem()
    : FormFactorItem(Constants::HemiEllipsoidType)
{
    addProperty(P_RADIUS_X, 10.0);
    addProperty(P_RADIUS_Y, 6.0);
    addProperty(P_HEIGHT, 8.0);
}

std::unique_ptr<IFormFactor> HemiEllipsoidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorHemiEllipsoid>(
                getItemValue(P_RADIUS_X).toDouble(),
                getItemValue(P_RADIUS_Y).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString IcosahedronItem::P_EDGE = QString::fromStdString(BornAgain::Edge);

IcosahedronItem::IcosahedronItem()
    : FormFactorItem(Constants::IcosahedronType)
{
    addProperty(P_EDGE, 10.0);
}

std::unique_ptr<IFormFactor> IcosahedronItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorIcosahedron>(
                getItemValue(P_EDGE).toDouble()
                );
}


/* ------------------------------------------------ */

const QString Prism3Item::P_BASEEDGE = QString::fromStdString(BornAgain::BaseEdge);
const QString Prism3Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);

Prism3Item::Prism3Item()
    : FormFactorItem(Constants::Prism3Type)
{
    addProperty(P_BASEEDGE, 10.0);
    addProperty(P_HEIGHT, 13.0);
}

std::unique_ptr<IFormFactor> Prism3Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorPrism3>(
                getItemValue(P_BASEEDGE).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString Prism6Item::P_BASEEDGE = QString::fromStdString(BornAgain::BaseEdge);
const QString Prism6Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);

Prism6Item::Prism6Item()
    : FormFactorItem(Constants::Prism6Type)
{
    addProperty(P_BASEEDGE, 5.0);
    addProperty(P_HEIGHT, 11.0);
}

std::unique_ptr<IFormFactor> Prism6Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorPrism6>(
                getItemValue(P_BASEEDGE).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString PyramidItem::P_BASEEDGE = QString::fromStdString(BornAgain::BaseEdge);
const QString PyramidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString PyramidItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

PyramidItem::PyramidItem()
    : FormFactorItem(Constants::PyramidType)
{
    addProperty(P_BASEEDGE, 18.0);
    addProperty(P_HEIGHT, 13.0);
    addProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> PyramidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorPyramid>(
                getItemValue(P_BASEEDGE).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_ALPHA).toDouble()*Units::degree
                );
}

/* ------------------------------------------------ */

const QString Ripple1Item::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString Ripple1Item::P_WIDTH = QString::fromStdString(BornAgain::Width);
const QString Ripple1Item::P_HEIGHT = QString::fromStdString(BornAgain::Height);

Ripple1Item::Ripple1Item()
    : FormFactorItem(Constants::Ripple1Type)
{
    addProperty(P_LENGTH, 27.0);
    addProperty(P_WIDTH, 20.0);
    addProperty(P_HEIGHT, 14.0);
}

std::unique_ptr<IFormFactor> Ripple1Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorRipple1>(
                getItemValue(P_LENGTH).toDouble(),
                getItemValue(P_WIDTH).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
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
    addProperty(P_LENGTH, 36.0);
    addProperty(P_WIDTH, 25.0);
    addProperty(P_HEIGHT, 14.0);
    addProperty(P_ASYMMETRY, 3.0);
}

std::unique_ptr<IFormFactor> Ripple2Item::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorRipple2>(
                getItemValue(P_LENGTH).toDouble(),
                getItemValue(P_WIDTH).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_ASYMMETRY).toDouble()
                );
}

/* ------------------------------------------------ */

const QString TetrahedronItem::P_BASEEDGE = QString::fromStdString(BornAgain::BaseEdge);
const QString TetrahedronItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString TetrahedronItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

TetrahedronItem::TetrahedronItem()
    : FormFactorItem(Constants::TetrahedronType)
{
    addProperty(P_BASEEDGE, 15.0);
    addProperty(P_HEIGHT, 6.0);
    addProperty(P_ALPHA, 60.0);
}

std::unique_ptr<IFormFactor> TetrahedronItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTetrahedron>(
                getItemValue(P_BASEEDGE).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_ALPHA).toDouble()*Units::degree
                );
}


/* ------------------------------------------------ */

const QString TruncatedCubeItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString TruncatedCubeItem::P_REMOVED_LENGTH = QString::fromStdString(BornAgain::RemovedLength);

TruncatedCubeItem::TruncatedCubeItem()
    : FormFactorItem(Constants::TruncatedCubeType)
{
    addProperty(P_LENGTH, 15.0);
    addProperty(P_REMOVED_LENGTH, 6.0);
}

std::unique_ptr<IFormFactor> TruncatedCubeItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTruncatedCube>(
                getItemValue(P_LENGTH).toDouble(),
                getItemValue(P_REMOVED_LENGTH).toDouble()
                );
}

/* ------------------------------------------------ */

const QString TruncatedSphereItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString TruncatedSphereItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

TruncatedSphereItem::TruncatedSphereItem()
    : FormFactorItem(Constants::TruncatedSphereType)
{
    addProperty(P_RADIUS, 5.0);
    addProperty(P_HEIGHT, 7.0);
}

std::unique_ptr<IFormFactor> TruncatedSphereItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTruncatedSphere>(
                getItemValue(P_RADIUS).toDouble(),
                getItemValue(P_HEIGHT).toDouble()
                );
}

/* ------------------------------------------------ */

const QString TruncatedSpheroidItem::P_RADIUS = QString::fromStdString(BornAgain::Radius);
const QString TruncatedSpheroidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString TruncatedSpheroidItem::P_HFC = QString::fromStdString(BornAgain::HeightFlattening);

TruncatedSpheroidItem::TruncatedSpheroidItem()
    : FormFactorItem(Constants::TruncatedSpheroidType)
{
    addProperty(P_RADIUS, 7.5);
    addProperty(P_HEIGHT, 9.0);
    addProperty(P_HFC, 1.2);
}

std::unique_ptr<IFormFactor> TruncatedSpheroidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTruncatedSpheroid>(
                getItemValue(P_RADIUS).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_HFC).toDouble()
                );
}
