// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FormFactorItems.cpp
//! @brief     Implements FormFactorItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/FormFactorItems.h"
#include "Core/Parametrization/Units.h"
#include "Core/includeIncludes/FormFactors.h"

/* ------------------------------------------------ */

const QString AnisoPyramidItem::P_LENGTH = QString::fromStdString("Length");
const QString AnisoPyramidItem::P_WIDTH = QString::fromStdString("Width");
const QString AnisoPyramidItem::P_HEIGHT = QString::fromStdString("Height");
const QString AnisoPyramidItem::P_ALPHA = QString::fromStdString("Alpha");

AnisoPyramidItem::AnisoPyramidItem() : FormFactorItem(Constants::AnisoPyramidType)
{
    setToolTip(QStringLiteral("A truncated pyramid with a rectangular base"));
    addProperty(P_LENGTH, 20.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nanometers"));
    addProperty(P_WIDTH, 16.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nanometers"));
    addProperty(P_HEIGHT, 13.0)->setToolTip(QStringLiteral("Height of pyramid in nanometers"));
    addProperty(P_ALPHA, 60.0)
        ->setToolTip(QStringLiteral("Dihedral angle in degrees between base and facet"));
}

std::unique_ptr<IFormFactor> AnisoPyramidItem::createFormFactor() const
{
    return std::make_unique<FormFactorAnisoPyramid>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_WIDTH).toDouble(),
        getItemValue(P_HEIGHT).toDouble(), getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString BarGaussItem::P_LENGTH = QString::fromStdString("Length");
const QString BarGaussItem::P_WIDTH = QString::fromStdString("Width");
const QString BarGaussItem::P_HEIGHT = QString::fromStdString("Height");

BarGaussItem::BarGaussItem() : FormFactorItem(Constants::BarGaussType)
{
    setToolTip(QStringLiteral("Rectangular cuboid"));
    addProperty(P_LENGTH, 20.0)->setToolTip(QStringLiteral("Length of the base in nanometers"));
    addProperty(P_WIDTH, 16.0)->setToolTip(QStringLiteral("Width of the base in nanometers"));
    addProperty(P_HEIGHT, 13.0)->setToolTip(QStringLiteral("Height of the box in nanometers"));
}

std::unique_ptr<IFormFactor> BarGaussItem::createFormFactor() const
{
    return std::make_unique<FormFactorBarGauss>(getItemValue(P_LENGTH).toDouble(),
                                                getItemValue(P_WIDTH).toDouble(),
                                                getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString BarLorentzItem::P_LENGTH = QString::fromStdString("Length");
const QString BarLorentzItem::P_WIDTH = QString::fromStdString("Width");
const QString BarLorentzItem::P_HEIGHT = QString::fromStdString("Height");

BarLorentzItem::BarLorentzItem() : FormFactorItem(Constants::BarLorentzType)
{
    setToolTip(QStringLiteral("Rectangular cuboid"));
    addProperty(P_LENGTH, 20.0)->setToolTip(QStringLiteral("Length of the base in nanometers"));
    addProperty(P_WIDTH, 16.0)->setToolTip(QStringLiteral("Width of the base in nanometers"));
    addProperty(P_HEIGHT, 13.0)->setToolTip(QStringLiteral("Height of the box in nanometers"));
}

std::unique_ptr<IFormFactor> BarLorentzItem::createFormFactor() const
{
    return std::make_unique<FormFactorBarLorentz>(getItemValue(P_LENGTH).toDouble(),
                                                  getItemValue(P_WIDTH).toDouble(),
                                                  getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString BoxItem::P_LENGTH = QString::fromStdString("Length");
const QString BoxItem::P_WIDTH = QString::fromStdString("Width");
const QString BoxItem::P_HEIGHT = QString::fromStdString("Height");

BoxItem::BoxItem() : FormFactorItem(Constants::BoxType)
{
    setToolTip(QStringLiteral("Rectangular cuboid"));
    addProperty(P_LENGTH, 20.0)->setToolTip(QStringLiteral("Length of the base in nanometers"));
    addProperty(P_WIDTH, 16.0)->setToolTip(QStringLiteral("Width of the base in nanometers"));
    addProperty(P_HEIGHT, 13.0)->setToolTip(QStringLiteral("Height of the box in nanometers"));
}

std::unique_ptr<IFormFactor> BoxItem::createFormFactor() const
{
    return std::make_unique<FormFactorBox>(getItemValue(P_LENGTH).toDouble(),
                                           getItemValue(P_WIDTH).toDouble(),
                                           getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString ConeItem::P_RADIUS = QString::fromStdString("Radius");
const QString ConeItem::P_HEIGHT = QString::fromStdString("Height");
const QString ConeItem::P_ALPHA = QString::fromStdString("Alpha");

ConeItem::ConeItem() : FormFactorItem(Constants::ConeType)
{
    setToolTip(QStringLiteral("Truncated cone with circular base"));
    addProperty(P_RADIUS, 10.0)->setToolTip(QStringLiteral("Radius of the base in nanometers"));
    addProperty(P_HEIGHT, 13.0)->setToolTip(QStringLiteral("Height of the cone in nanometers"));
    addProperty(P_ALPHA, 60.0)
        ->setToolTip(QStringLiteral("Angle between the base and the side surface in degrees"));
}

std::unique_ptr<IFormFactor> ConeItem::createFormFactor() const
{
    return std::make_unique<FormFactorCone>(getItemValue(P_RADIUS).toDouble(),
                                            getItemValue(P_HEIGHT).toDouble(),
                                            getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString Cone6Item::P_BASEEDGE = QString::fromStdString("BaseEdge");
const QString Cone6Item::P_HEIGHT = QString::fromStdString("Height");
const QString Cone6Item::P_ALPHA = QString::fromStdString("Alpha");

Cone6Item::Cone6Item() : FormFactorItem(Constants::Cone6Type)
{
    setToolTip(QStringLiteral("A truncated pyramid, based on a regular hexagon"));
    addProperty(P_BASEEDGE, 10.0)
        ->setToolTip(QStringLiteral("Edge of the regular hexagonal base in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of a truncated pyramid in nanometers"));
    addProperty(P_ALPHA, 60.0)
        ->setToolTip(QStringLiteral("Dihedral angle in degrees between base and facet"));
}

std::unique_ptr<IFormFactor> Cone6Item::createFormFactor() const
{
    return std::make_unique<FormFactorCone6>(getItemValue(P_BASEEDGE).toDouble(),
                                             getItemValue(P_HEIGHT).toDouble(),
                                             getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString CuboctahedronItem::P_LENGTH = QString::fromStdString("Length");
const QString CuboctahedronItem::P_HEIGHT = QString::fromStdString("Height");
const QString CuboctahedronItem::P_HEIGHT_RATIO = QString::fromStdString("HeightRatio");
const QString CuboctahedronItem::P_ALPHA = QString::fromStdString("Alpha");

CuboctahedronItem::CuboctahedronItem() : FormFactorItem(Constants::CuboctahedronType)
{
    setToolTip(QStringLiteral("Compound of two truncated pyramids with a common square base \n"
                              "and opposite orientations"));
    addProperty(P_LENGTH, 20.0)
        ->setToolTip(QStringLiteral("Side length of the common square base in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of the lower pyramid in nanometers"));
    addProperty(P_HEIGHT_RATIO, 0.7)
        ->setLimits(RealLimits::lowerLimited(0.0))
        .setToolTip(QStringLiteral("Ratio of heights of top to bottom pyramids"));
    addProperty(P_ALPHA, 60.0)
        ->setToolTip(QStringLiteral("Dihedral angle in degrees between base and facets"));
}

std::unique_ptr<IFormFactor> CuboctahedronItem::createFormFactor() const
{
    return std::make_unique<FormFactorCuboctahedron>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_HEIGHT).toDouble(),
        getItemValue(P_HEIGHT_RATIO).toDouble(), getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString CylinderItem::P_RADIUS = QString::fromStdString("Radius");
const QString CylinderItem::P_HEIGHT = QString::fromStdString("Height");

CylinderItem::CylinderItem() : FormFactorItem(Constants::CylinderType)
{
    setToolTip(QStringLiteral("Cylinder with a circular base"));
    addProperty(P_RADIUS, 8.0)
        ->setToolTip(QStringLiteral("Radius of the circular base in nanometers"));
    addProperty(P_HEIGHT, 16.0)->setToolTip(QStringLiteral("Height of the cylinder in nanometers"));
}

std::unique_ptr<IFormFactor> CylinderItem::createFormFactor() const
{
    return std::make_unique<FormFactorCylinder>(getItemValue(P_RADIUS).toDouble(),
                                                getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString DodecahedronItem::P_EDGE = QString::fromStdString("Edge");

DodecahedronItem::DodecahedronItem() : FormFactorItem(Constants::DodecahedronType)
{
    setToolTip(QStringLiteral("Dodecahedron"));
    addProperty(P_EDGE, 10.0)->setToolTip(QStringLiteral("Length of the edge in nanometers"));
}

std::unique_ptr<IFormFactor> DodecahedronItem::createFormFactor() const
{
    return std::make_unique<FormFactorDodecahedron>(getItemValue(P_EDGE).toDouble());
}

/* ------------------------------------------------ */

const QString DotItem::P_RADIUS = QString::fromStdString("Radius");

DotItem::DotItem() : FormFactorItem(Constants::DotType)
{
    setToolTip(QStringLiteral("A dot, with constant formfactor F(q)=4pi/3 R^3"));
    addProperty(P_RADIUS, 8.0)
        ->setToolTip(QStringLiteral("Radius of reference sphere in nanometers"));
}

std::unique_ptr<IFormFactor> DotItem::createFormFactor() const
{
    return std::make_unique<FormFactorDot>(getItemValue(P_RADIUS).toDouble());
}

/* ------------------------------------------------ */

const QString EllipsoidalCylinderItem::P_RADIUS_X = QString::fromStdString("RadiusX");
const QString EllipsoidalCylinderItem::P_RADIUS_Y = QString::fromStdString("RadiusY");
const QString EllipsoidalCylinderItem::P_HEIGHT = QString::fromStdString("Height");

EllipsoidalCylinderItem::EllipsoidalCylinderItem()
    : FormFactorItem(Constants::EllipsoidalCylinderType)
{
    setToolTip(QStringLiteral("Cylinder with an ellipse cross section"));
    addProperty(P_RADIUS_X, 8.0)
        ->setToolTip(
            QStringLiteral("Radius of the ellipse base in the x-direction, in nanometers"));
    addProperty(P_RADIUS_Y, 13.0)
        ->setToolTip(
            QStringLiteral("Radius of the ellipse base in the y-direction, in nanometers"));
    addProperty(P_HEIGHT, 16.0)
        ->setToolTip(QStringLiteral("Height of the ellipsoidal cylinder in nanometers"));
}

std::unique_ptr<IFormFactor> EllipsoidalCylinderItem::createFormFactor() const
{
    return std::make_unique<FormFactorEllipsoidalCylinder>(getItemValue(P_RADIUS_X).toDouble(),
                                                           getItemValue(P_RADIUS_Y).toDouble(),
                                                           getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString FullSphereItem::P_RADIUS = QString::fromStdString("Radius");

FullSphereItem::FullSphereItem() : FormFactorItem(Constants::FullSphereType)
{
    setToolTip(QStringLiteral("Full sphere"));
    addProperty(P_RADIUS, 8.0)->setToolTip(QStringLiteral("Radius of the sphere in nanometers"));
}

std::unique_ptr<IFormFactor> FullSphereItem::createFormFactor() const
{
    return std::make_unique<FormFactorFullSphere>(getItemValue(P_RADIUS).toDouble());
}

/* ------------------------------------------------ */

const QString FullSpheroidItem::P_RADIUS = QString::fromStdString("Radius");
const QString FullSpheroidItem::P_HEIGHT = QString::fromStdString("Height");

FullSpheroidItem::FullSpheroidItem() : FormFactorItem(Constants::FullSpheroidType)
{
    setToolTip(
        QStringLiteral("Full spheroid, generated by rotating an ellipse around the vertical axis"));
    addProperty(P_RADIUS, 10.0)
        ->setToolTip(QStringLiteral("Radius of the circular cross section in nanometers"));
    addProperty(P_HEIGHT, 13.0)
        ->setToolTip(QStringLiteral("Height of the full spheroid in nanometers"));
}

std::unique_ptr<IFormFactor> FullSpheroidItem::createFormFactor() const
{
    return std::make_unique<FormFactorFullSpheroid>(getItemValue(P_RADIUS).toDouble(),
                                                    getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString HemiEllipsoidItem::P_RADIUS_X = QString::fromStdString("RadiusX");
const QString HemiEllipsoidItem::P_RADIUS_Y = QString::fromStdString("RadiusY");
const QString HemiEllipsoidItem::P_HEIGHT = QString::fromStdString("Height");

HemiEllipsoidItem::HemiEllipsoidItem() : FormFactorItem(Constants::HemiEllipsoidType)
{
    setToolTip(
        QStringLiteral("An horizontally oriented ellipsoid, truncated at the central plane"));
    addProperty(P_RADIUS_X, 10.0)
        ->setToolTip(
            QStringLiteral("Radius of the ellipse base in the x-direction, in nanometers"));
    addProperty(P_RADIUS_Y, 6.0)
        ->setToolTip(
            QStringLiteral("Radius of the ellipse base in the y-direction, in nanometers"));
    addProperty(P_HEIGHT, 8.0)
        ->setToolTip(QStringLiteral("Height of the hemi ellipsoid in nanometers"));
}

std::unique_ptr<IFormFactor> HemiEllipsoidItem::createFormFactor() const
{
    return std::make_unique<FormFactorHemiEllipsoid>(getItemValue(P_RADIUS_X).toDouble(),
                                                     getItemValue(P_RADIUS_Y).toDouble(),
                                                     getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString IcosahedronItem::P_EDGE = QString::fromStdString("Edge");

IcosahedronItem::IcosahedronItem() : FormFactorItem(Constants::IcosahedronType)
{
    setToolTip(QStringLiteral("Icosahedron"));
    addProperty(P_EDGE, 10.0)->setToolTip(QStringLiteral("Length of the edge in nanometers"));
}

std::unique_ptr<IFormFactor> IcosahedronItem::createFormFactor() const
{
    return std::make_unique<FormFactorIcosahedron>(getItemValue(P_EDGE).toDouble());
}

/* ------------------------------------------------ */

const QString Prism3Item::P_BASEEDGE = QString::fromStdString("BaseEdge");
const QString Prism3Item::P_HEIGHT = QString::fromStdString("Height");

Prism3Item::Prism3Item() : FormFactorItem(Constants::Prism3Type)
{
    setToolTip(QStringLiteral("Prism with an equilaterial triangle base"));
    addProperty(P_BASEEDGE, 10.0)
        ->setToolTip(QStringLiteral("Length of the base edge in nanometers"));
    addProperty(P_HEIGHT, 13.0)->setToolTip(QStringLiteral("Height in nanometers"));
}

std::unique_ptr<IFormFactor> Prism3Item::createFormFactor() const
{
    return std::make_unique<FormFactorPrism3>(getItemValue(P_BASEEDGE).toDouble(),
                                              getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString Prism6Item::P_BASEEDGE = QString::fromStdString("BaseEdge");
const QString Prism6Item::P_HEIGHT = QString::fromStdString("Height");

Prism6Item::Prism6Item() : FormFactorItem(Constants::Prism6Type)
{
    setToolTip(QStringLiteral("Prism with a regular hexagonal base"));
    addProperty(P_BASEEDGE, 5.0)
        ->setToolTip(QStringLiteral("Length of the hexagonal base in nanometers"));
    addProperty(P_HEIGHT, 11.0)->setToolTip(QStringLiteral("Height in nanometers"));
}

std::unique_ptr<IFormFactor> Prism6Item::createFormFactor() const
{
    return std::make_unique<FormFactorPrism6>(getItemValue(P_BASEEDGE).toDouble(),
                                              getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString PyramidItem::P_BASEEDGE = QString::fromStdString("BaseEdge");
const QString PyramidItem::P_HEIGHT = QString::fromStdString("Height");
const QString PyramidItem::P_ALPHA = QString::fromStdString("Alpha");

PyramidItem::PyramidItem() : FormFactorItem(Constants::PyramidType)
{
    setToolTip(QStringLiteral("Truncated pyramid with a square base"));
    addProperty(P_BASEEDGE, 18.0)
        ->setToolTip(QStringLiteral("Length of the square base in nanometers"));
    addProperty(P_HEIGHT, 13.0)->setToolTip(QStringLiteral("Height of the pyramid in nanometers"));
    addProperty(P_ALPHA, 60.0)
        ->setToolTip(QStringLiteral("Dihedral angle between the base and a side face in degrees"));
}

std::unique_ptr<IFormFactor> PyramidItem::createFormFactor() const
{
    return std::make_unique<FormFactorPyramid>(getItemValue(P_BASEEDGE).toDouble(),
                                               getItemValue(P_HEIGHT).toDouble(),
                                               getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString Ripple1BoxItem::P_LENGTH = QString::fromStdString("Length");
const QString Ripple1BoxItem::P_WIDTH = QString::fromStdString("Width");
const QString Ripple1BoxItem::P_HEIGHT = QString::fromStdString("Height");

Ripple1BoxItem::Ripple1BoxItem() : FormFactorItem(Constants::Ripple1BoxType)
{
    setToolTip(QStringLiteral("Particle with a cosine profile and a rectangular base"));
    addProperty(P_LENGTH, 27.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nanometers"));
    addProperty(P_WIDTH, 20.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nanometers"));
    addProperty(P_HEIGHT, 14.0)->setToolTip(QStringLiteral("Height of the ripple in nanometers"));
}

std::unique_ptr<IFormFactor> Ripple1BoxItem::createFormFactor() const
{
    return std::make_unique<FormFactorRipple1Box>(getItemValue(P_LENGTH).toDouble(),
                                                  getItemValue(P_WIDTH).toDouble(),
                                                  getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString Ripple1GaussItem::P_LENGTH = QString::fromStdString("Length");
const QString Ripple1GaussItem::P_WIDTH = QString::fromStdString("Width");
const QString Ripple1GaussItem::P_HEIGHT = QString::fromStdString("Height");

Ripple1GaussItem::Ripple1GaussItem() : FormFactorItem(Constants::Ripple1GaussType)
{
    setToolTip(QStringLiteral("Particle with a cosine profile and a rectangular base"));
    addProperty(P_LENGTH, 27.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nanometers"));
    addProperty(P_WIDTH, 20.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nanometers"));
    addProperty(P_HEIGHT, 14.0)->setToolTip(QStringLiteral("Height of the ripple in nanometers"));
}

std::unique_ptr<IFormFactor> Ripple1GaussItem::createFormFactor() const
{
    return std::make_unique<FormFactorRipple1Gauss>(getItemValue(P_LENGTH).toDouble(),
                                                    getItemValue(P_WIDTH).toDouble(),
                                                    getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString Ripple1LorentzItem::P_LENGTH = QString::fromStdString("Length");
const QString Ripple1LorentzItem::P_WIDTH = QString::fromStdString("Width");
const QString Ripple1LorentzItem::P_HEIGHT = QString::fromStdString("Height");

Ripple1LorentzItem::Ripple1LorentzItem() : FormFactorItem(Constants::Ripple1LorentzType)
{
    setToolTip(QStringLiteral("Particle with a cosine profile and a rectangular base"));
    addProperty(P_LENGTH, 27.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nanometers"));
    addProperty(P_WIDTH, 20.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nanometers"));
    addProperty(P_HEIGHT, 14.0)->setToolTip(QStringLiteral("Height of the ripple in nanometers"));
}

std::unique_ptr<IFormFactor> Ripple1LorentzItem::createFormFactor() const
{
    return std::make_unique<FormFactorRipple1Lorentz>(getItemValue(P_LENGTH).toDouble(),
                                                      getItemValue(P_WIDTH).toDouble(),
                                                      getItemValue(P_HEIGHT).toDouble());
}

/* ------------------------------------------------ */

const QString Ripple2BoxItem::P_LENGTH = QString::fromStdString("Length");
const QString Ripple2BoxItem::P_WIDTH = QString::fromStdString("Width");
const QString Ripple2BoxItem::P_HEIGHT = QString::fromStdString("Height");
const QString Ripple2BoxItem::P_ASYMMETRY = QString::fromStdString("AsymmetryLength");

Ripple2BoxItem::Ripple2BoxItem() : FormFactorItem(Constants::Ripple2BoxType)
{
    setToolTip(
        QStringLiteral("Particle with an asymmetric triangle profile and a rectangular base"));
    addProperty(P_LENGTH, 36.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nanometers"));
    addProperty(P_WIDTH, 25.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nanometers"));
    addProperty(P_HEIGHT, 14.0)->setToolTip(QStringLiteral("Height of the ripple in nanometers"));
    addProperty(P_ASYMMETRY, 3.0)
        ->setToolTip(QStringLiteral("Asymmetry length of the triangular profile in nanometers"));
}

std::unique_ptr<IFormFactor> Ripple2BoxItem::createFormFactor() const
{
    return std::make_unique<FormFactorRipple2Box>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_WIDTH).toDouble(),
        getItemValue(P_HEIGHT).toDouble(), getItemValue(P_ASYMMETRY).toDouble());
}

/* ------------------------------------------------ */

const QString Ripple2GaussItem::P_LENGTH = QString::fromStdString("Length");
const QString Ripple2GaussItem::P_WIDTH = QString::fromStdString("Width");
const QString Ripple2GaussItem::P_HEIGHT = QString::fromStdString("Height");
const QString Ripple2GaussItem::P_ASYMMETRY = QString::fromStdString("AsymmetryLength");

Ripple2GaussItem::Ripple2GaussItem() : FormFactorItem(Constants::Ripple2GaussType)
{
    setToolTip(
        QStringLiteral("Particle with an asymmetric triangle profile and a rectangular base"));
    addProperty(P_LENGTH, 36.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nanometers"));
    addProperty(P_WIDTH, 25.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nanometers"));
    addProperty(P_HEIGHT, 14.0)->setToolTip(QStringLiteral("Height of the ripple in nanometers"));
    addProperty(P_ASYMMETRY, 3.0)
        ->setToolTip(QStringLiteral("Asymmetry length of the triangular profile in nanometers"));
}

std::unique_ptr<IFormFactor> Ripple2GaussItem::createFormFactor() const
{
    return std::make_unique<FormFactorRipple2Gauss>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_WIDTH).toDouble(),
        getItemValue(P_HEIGHT).toDouble(), getItemValue(P_ASYMMETRY).toDouble());
}

/* ------------------------------------------------ */

const QString Ripple2LorentzItem::P_LENGTH = QString::fromStdString("Length");
const QString Ripple2LorentzItem::P_WIDTH = QString::fromStdString("Width");
const QString Ripple2LorentzItem::P_HEIGHT = QString::fromStdString("Height");
const QString Ripple2LorentzItem::P_ASYMMETRY = QString::fromStdString("AsymmetryLength");

Ripple2LorentzItem::Ripple2LorentzItem() : FormFactorItem(Constants::Ripple2LorentzType)
{
    setToolTip(
        QStringLiteral("Particle with an asymmetric triangle profile and a rectangular base"));
    addProperty(P_LENGTH, 36.0)
        ->setToolTip(QStringLiteral("Length of the rectangular base in nanometers"));
    addProperty(P_WIDTH, 25.0)
        ->setToolTip(QStringLiteral("Width of the rectangular base in nanometers"));
    addProperty(P_HEIGHT, 14.0)->setToolTip(QStringLiteral("Height of the ripple in nanometers"));
    addProperty(P_ASYMMETRY, 3.0)
        ->setToolTip(QStringLiteral("Asymmetry length of the triangular profile in nanometers"));
}

std::unique_ptr<IFormFactor> Ripple2LorentzItem::createFormFactor() const
{
    return std::make_unique<FormFactorRipple2Lorentz>(
        getItemValue(P_LENGTH).toDouble(), getItemValue(P_WIDTH).toDouble(),
        getItemValue(P_HEIGHT).toDouble(), getItemValue(P_ASYMMETRY).toDouble());
}

/* ------------------------------------------------ */

const QString TetrahedronItem::P_BASEEDGE = QString::fromStdString("BaseEdge");
const QString TetrahedronItem::P_HEIGHT = QString::fromStdString("Height");
const QString TetrahedronItem::P_ALPHA = QString::fromStdString("Alpha");

TetrahedronItem::TetrahedronItem() : FormFactorItem(Constants::TetrahedronType)
{
    setToolTip(QStringLiteral("A truncated tethrahedron"));
    addProperty(P_BASEEDGE, 15.0)
        ->setToolTip(
            QStringLiteral("Length of one edge of the equilateral triangular base in nanometers"));
    addProperty(P_HEIGHT, 6.0)
        ->setToolTip(QStringLiteral("Height of the tetrahedron in nanometers"));
    addProperty(P_ALPHA, 60.0)
        ->setToolTip(QStringLiteral("Dihedral angle in degrees between base and facet"));
}

std::unique_ptr<IFormFactor> TetrahedronItem::createFormFactor() const
{
    return std::make_unique<FormFactorTetrahedron>(
        getItemValue(P_BASEEDGE).toDouble(), getItemValue(P_HEIGHT).toDouble(),
        getItemValue(P_ALPHA).toDouble() * Units::degree);
}

/* ------------------------------------------------ */

const QString TruncatedCubeItem::P_LENGTH = QString::fromStdString("Length");
const QString TruncatedCubeItem::P_REMOVED_LENGTH =
    QString::fromStdString("RemovedLength");

TruncatedCubeItem::TruncatedCubeItem() : FormFactorItem(Constants::TruncatedCubeType)
{
    setToolTip(QStringLiteral("A cube whose eight vertices have been removed"));
    addProperty(P_LENGTH, 15.0)
        ->setToolTip(QStringLiteral("Length of the full cube's edge in nanometers"));
    addProperty(P_REMOVED_LENGTH, 6.0)
        ->setToolTip(QStringLiteral("Removed length from each edge of the cube in nanometers"));
}

std::unique_ptr<IFormFactor> TruncatedCubeItem::createFormFactor() const
{
    return std::make_unique<FormFactorTruncatedCube>(getItemValue(P_LENGTH).toDouble(),
                                                     getItemValue(P_REMOVED_LENGTH).toDouble());
}

/* ------------------------------------------------ */

const QString TruncatedSphereItem::P_RADIUS = QString::fromStdString("Radius");
const QString TruncatedSphereItem::P_HEIGHT = QString::fromStdString("Height");
const QString TruncatedSphereItem::P_REMOVED_TOP = QString::fromStdString("DeltaHeight");

TruncatedSphereItem::TruncatedSphereItem() : FormFactorItem(Constants::TruncatedSphereType)
{
    setToolTip(QStringLiteral("Spherical dome"));
    addProperty(P_RADIUS, 5.0)
        ->setToolTip(QStringLiteral("Radius of the truncated sphere in nanometers"));
    addProperty(P_HEIGHT, 7.0)
        ->setToolTip(QStringLiteral("Height of the truncated sphere in nanometers"));
    addProperty(P_REMOVED_TOP, 0.0)
        ->setToolTip(QStringLiteral("Height of the removed top cap in nanometers"));
}

std::unique_ptr<IFormFactor> TruncatedSphereItem::createFormFactor() const
{
    return std::make_unique<FormFactorTruncatedSphere>(getItemValue(P_RADIUS).toDouble(),
                                                       getItemValue(P_HEIGHT).toDouble(),
                                                       getItemValue(P_REMOVED_TOP).toDouble());
}

/* ------------------------------------------------ */

const QString TruncatedSpheroidItem::P_RADIUS = QString::fromStdString("Radius");
const QString TruncatedSpheroidItem::P_HEIGHT = QString::fromStdString("Height");
const QString TruncatedSpheroidItem::P_HFC = QString::fromStdString("HeightFlattening");
const QString TruncatedSpheroidItem::P_REMOVED_TOP = QString::fromStdString("DeltaHeight");

TruncatedSpheroidItem::TruncatedSpheroidItem() : FormFactorItem(Constants::TruncatedSpheroidType)
{
    setToolTip(QStringLiteral("Spheroidal dome"));
    addProperty(P_RADIUS, 7.5)
        ->setToolTip(QStringLiteral("Radius of the truncated spheroid in nanometers"));
    addProperty(P_HEIGHT, 9.0)
        ->setToolTip(QStringLiteral("Height of the truncated spheroid in nanometers"));
    addProperty(P_HFC, 1.2)
        ->setToolTip(QStringLiteral(
            "Ratio of the height of the corresponding full spheroid to its diameter"));
    addProperty(P_REMOVED_TOP, 0.0)
        ->setToolTip(QStringLiteral("Height of the removed top cap in nanometers"));
}

std::unique_ptr<IFormFactor> TruncatedSpheroidItem::createFormFactor() const
{
    return std::make_unique<FormFactorTruncatedSpheroid>(
        getItemValue(P_RADIUS).toDouble(), getItemValue(P_HEIGHT).toDouble(),
        getItemValue(P_HFC).toDouble(), getItemValue(P_REMOVED_TOP).toDouble());
}
