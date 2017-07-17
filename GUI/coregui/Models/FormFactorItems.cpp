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
#include "BornAgainNamespace.h"
#include "FormFactors.h"
#include "GUIHelpers.h"
#include "Units.h"

/* ------------------------------------------------ */

const QString AnisoPyramidItem::P_LENGTH = QString::fromStdString(BornAgain::Length);
const QString AnisoPyramidItem::P_WIDTH = QString::fromStdString(BornAgain::Width);
const QString AnisoPyramidItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);
const QString AnisoPyramidItem::P_ALPHA = QString::fromStdString(BornAgain::Alpha);

AnisoPyramidItem::AnisoPyramidItem()
    : FormFactorItem(Constants::AnisoPyramidType)
{
    setToolTip(QStringLiteral("A truncated pyramid with a rectangular base"));
    addProperty(P_LENGTH, 20.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nanometers"));
    addProperty(P_WIDTH, 16.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of pyramid in nanometers"));
    addProperty(P_ALPHA, 60.0)->setToolTip(
        QStringLiteral("Dihedral angle in degrees between base and facet"));
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
    setToolTip(QStringLiteral("Rectangular cuboid"));
    addProperty(P_LENGTH, 20.0)
        ->setToolTip(QStringLiteral("Length of the base in nanometers"));
    addProperty(P_WIDTH, 16.0)
        ->setToolTip(QStringLiteral("Width of the base in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of the box in nanometers"));
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
    setToolTip(QStringLiteral("Truncated cone with circular base"));
    addProperty(P_RADIUS, 10.0)
        ->setToolTip(QStringLiteral("Radius of the base in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of the cone in nanometers"));
    addProperty(P_ALPHA, 60.0)
        ->setToolTip(QStringLiteral("Angle between the side and the base in degrees"));
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
    setToolTip(QStringLiteral("A truncated pyramid, based on a regular hexagon"));
    addProperty(P_BASEEDGE, 10.0)
        ->setToolTip(QStringLiteral("Edge of the regular hexagonal base in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of frustum in nanometers"));
    addProperty(P_ALPHA, 60.0)->setToolTip(
        QStringLiteral("Dihedral angle in degrees between base and facet"));

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
    setToolTip(QStringLiteral("Compound of two truncated pyramids with a common square base \n"
                              "and opposite orientations"));
    addProperty(P_LENGTH, 20.0)
        ->setToolTip(QStringLiteral("Side length of the common square base in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of the lower pyramid in nanometers"));
    addProperty(P_HEIGHT_RATIO, 0.7)->setLimits(RealLimits::lowerLimited(0.0))
        .setToolTip(QStringLiteral("Ratio of heights of top to bottom pyramids"));
    addProperty(P_ALPHA, 60.0)->setToolTip(
        QStringLiteral("Dihedral angle in degrees between base and facets"));
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
    setToolTip(QStringLiteral("Cylinder with a circular base"));
    addProperty(P_RADIUS, 8.0)
        ->setToolTip(QStringLiteral("Radius of the circular base in nanometers"));
    addProperty(P_HEIGHT, 16.0)
        ->setToolTip(QStringLiteral("Height of the cylinder in nanometers"));
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
    setToolTip(QStringLiteral("Dodecahedron"));
    addProperty(P_EDGE, 10.0)
        ->setToolTip(QStringLiteral("Length of the edge in nanometers"));
}

std::unique_ptr<IFormFactor> DodecahedronItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorDodecahedron>(
                getItemValue(P_EDGE).toDouble()
                );
}

/* ------------------------------------------------ */

DotItem::DotItem()
    : FormFactorItem(Constants::DotType)
{
    setToolTip(QStringLiteral("A dot, with trivial formfactor F(q)=1"));
}

std::unique_ptr<IFormFactor> DotItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorDot>();
}

/* ------------------------------------------------ */

const QString EllipsoidalCylinderItem::P_RADIUS_X = QString::fromStdString(BornAgain::RadiusX);
const QString EllipsoidalCylinderItem::P_RADIUS_Y = QString::fromStdString(BornAgain::RadiusY);
const QString EllipsoidalCylinderItem::P_HEIGHT = QString::fromStdString(BornAgain::Height);

EllipsoidalCylinderItem::EllipsoidalCylinderItem()
    : FormFactorItem(Constants::EllipsoidalCylinderType)
{
    setToolTip(QStringLiteral("Cylinder with an ellipse cross section"));
    addProperty(P_RADIUS_X, 8.0)->setToolTip(QStringLiteral(
        "Radius of the ellipse base in the x-direction, in nanometers"));
    addProperty(P_RADIUS_Y, 13.0)->setToolTip(QStringLiteral(
        "Radius of the ellipse base in the y-direction, in nanometers"));
    addProperty(P_HEIGHT, 16.0)
        ->setToolTip(QStringLiteral("Height of the ellipsoidal cylinder in nanometers"));
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
    setToolTip(QStringLiteral("Full sphere"));
    addProperty(P_RADIUS, 8.0)->setToolTip(QStringLiteral("Radius of the sphere in nanometers"));
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
    setToolTip(QStringLiteral(
        "Full spheroid, generated by rotating an ellipse around the vertical axis"));
    addProperty(P_RADIUS, 10.0)
        ->setToolTip(QStringLiteral("Radius of the circular cross section in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of the full spheroid in nanometers"));
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
    setToolTip(QStringLiteral(
               "An horizontally oriented ellipsoid, truncated at the central plane"));
    addProperty(P_RADIUS_X, 10.0)->setToolTip(QStringLiteral(
        "Radius of the ellipse base in the x-direction, in nanometers"));
    addProperty(P_RADIUS_Y, 6.0)->setToolTip(QStringLiteral(
        "Radius of the ellipse base in the y-direction, in nanometers"));
    addProperty(P_HEIGHT, 8.0)
        ->setToolTip(QStringLiteral("Height of the hemi ellipsoid in nanometers"));
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
    setToolTip(QStringLiteral("Icosahedron"));
    addProperty(P_EDGE, 10.0)
        ->setToolTip(QStringLiteral("Length of the edge in nanometers"));
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
    setToolTip(QStringLiteral("Prism with an equilaterial triangle base"));
    addProperty(P_BASEEDGE, 10.0)
        ->setToolTip(QStringLiteral("Length of the base edge in nm"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height in nm"));
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
    setToolTip(QStringLiteral("Prism with a regular hexagonal base"));
    addProperty(P_BASEEDGE, 5.0)
        ->setToolTip(QStringLiteral("Length of the hexagonal base in nm"));
    addProperty(P_HEIGHT, 11.0)
        ->setToolTip(QStringLiteral("Height in nm"));
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
    setToolTip(QStringLiteral("Truncated pyramid with a square base"));
    addProperty(P_BASEEDGE, 18.0)
        ->setToolTip(QStringLiteral("Length of the square base in nm"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of the pyramid in nm"));
    addProperty(P_ALPHA, 60.0)->setToolTip(QStringLiteral(
       "Angle between the base and the middle of the lateral faces in degrees"));
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
    setToolTip(QStringLiteral("Particle with a cosine profile and a rectangular base"));
    addProperty(P_LENGTH, 27.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nm"));
    addProperty(P_WIDTH, 20.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nm"));
    addProperty(P_HEIGHT, 14.0)
        ->setToolTip(QStringLiteral("Height of the ripple in nm"));
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
    setToolTip(QStringLiteral(
        "Particle with an asymmetric triangle profile and a rectangular base"));
    addProperty(P_LENGTH, 36.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nm"));
    addProperty(P_WIDTH, 25.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nm"));
    addProperty(P_HEIGHT, 14.0)
        ->setToolTip(QStringLiteral("Height of the ripple in nm"));
    addProperty(P_ASYMMETRY, 3.0)
        ->setToolTip(QStringLiteral("Asymmetry length of the triangular profile in nm"));
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
    setToolTip(QStringLiteral(
        "Truncated polyhedron with equilateral triangle base and cropped side faces"));
    addProperty(P_BASEEDGE, 15.0)
        ->setToolTip(QStringLiteral("Side length of the base in nm"));
    addProperty(P_HEIGHT, 6.0)
        ->setToolTip(QStringLiteral("Height of the tetrahedron in nm"));
    addProperty(P_ALPHA, 60.0)->setToolTip(QStringLiteral(
        "Angle between the base and the middle of the side faces in degrees"));
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
    setToolTip(QStringLiteral("A cube whose eight vertices have been removed"));
    addProperty(P_LENGTH, 15.0)
        ->setToolTip(QStringLiteral("Length of the full cube in nm"));
    addProperty(P_REMOVED_LENGTH, 6.0)->setToolTip(QStringLiteral(
        "Side length of the trirectangular tetrahedron removed from the cube’s vertices in nm"));
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
    setToolTip(QStringLiteral("Spherical dome"));
    addProperty(P_RADIUS, 5.0)
        ->setToolTip(QStringLiteral("Radius of the truncated sphere in nm"));
    addProperty(P_HEIGHT, 7.0)
        ->setToolTip(QStringLiteral("Height of the truncated sphere in nm"));
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
    setToolTip(QStringLiteral("Spheroidal dome"));
    addProperty(P_RADIUS, 7.5)
        ->setToolTip(QStringLiteral("Radius of the truncated spheroid in nm"));
    addProperty(P_HEIGHT, 9.0)
        ->setToolTip(QStringLiteral("Height of the truncated spheroid in nm"));
    addProperty(P_HFC, 1.2)->setToolTip(
        QStringLiteral("Ratio of the height of the corresponding full spheroid to its diameter"));
}

std::unique_ptr<IFormFactor> TruncatedSpheroidItem::createFormFactor() const
{
    return GUIHelpers::make_unique<FormFactorTruncatedSpheroid>(
                getItemValue(P_RADIUS).toDouble(),
                getItemValue(P_HEIGHT).toDouble(),
                getItemValue(P_HFC).toDouble()
                );
}

