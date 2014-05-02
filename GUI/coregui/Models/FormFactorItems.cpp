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

#include "FormFactorItems.h"
#include "FormFactors.h"
#include "Units.h"

AnisoPyramidItem::AnisoPyramidItem(ParameterizedItem *parent)
    : FormFactorItem(QString("AnisoPyramid"), parent)
{
    setItemName("AnisoPyramid");
    setProperty("Length", 20.0);
    setProperty("Width", 16.0);
    setProperty("Height", 13.0);
    setProperty("Alpha", 60.0);
}

IFormFactor *AnisoPyramidItem::createFormFactor() const
{
    return new FormFactorAnisoPyramid(
                property("Length").toDouble(),
                property("Width").toDouble(),
                property("Height").toDouble(),
                property("Alpha").toDouble()*Units::degree
                );
}



BoxItem::BoxItem(ParameterizedItem *parent)
    : FormFactorItem(QString("Box"), parent)
{
    setItemName("Box");
    setProperty("Length", 20.0);
    setProperty("Width", 16.0);
    setProperty("Height", 13.0);
}

IFormFactor *BoxItem::createFormFactor() const
{
    return new FormFactorBox(
                property("Length").toDouble(),
                property("Width").toDouble(),
                property("Height").toDouble()
                );
}


ConeItem::ConeItem(ParameterizedItem *parent)
    : FormFactorItem(QString("Cone"), parent)
{
    setItemName("Cone");
    setProperty("Radius", 10.0);
    setProperty("Height", 13.0);
    setProperty("Alpha", 60.0);
}

IFormFactor *ConeItem::createFormFactor() const
{
    return new FormFactorCone(
                property("Radius").toDouble(),
                property("Height").toDouble(),
                property("Alpha").toDouble()*Units::degree
                );
}


Cone6Item::Cone6Item(ParameterizedItem *parent)
    : FormFactorItem(QString("Cone6"), parent)
{
    setItemName("Cone6");
    setProperty("Radius", 10.0);
    setProperty("Height", 13.0);
    setProperty("Alpha", 60.0);
}

IFormFactor *Cone6Item::createFormFactor() const
{
    return new FormFactorCone6(
                property("Radius").toDouble(),
                property("Height").toDouble(),
                property("Alpha").toDouble()*Units::degree
                );
}


CuboctahedronItem::CuboctahedronItem(ParameterizedItem *parent)
    : FormFactorItem(QString("Cuboctahedron"), parent)
{
    setItemName("Cuboctahedron");
    setProperty("Length", 20.0);
    setProperty("Height", 13.0);
    setProperty("HeightRatio", 0.7);
    setProperty("Alpha", 60.0);
}

IFormFactor *CuboctahedronItem::createFormFactor() const
{
    return new FormFactorCuboctahedron(
                property("Length").toDouble(),
                property("Height").toDouble(),
                property("HeightRatio").toDouble(),
                property("Alpha").toDouble()*Units::degree
                );
}


CylinderItem::CylinderItem(ParameterizedItem *parent)
    : FormFactorItem(QString("Cylinder"), parent)
{
    setItemName("Cylinder");
    setProperty("Radius", 8.0);
    setProperty("Height", 16.0);
}

IFormFactor *CylinderItem::createFormFactor() const
{
    return new FormFactorCylinder(
                property("Radius").toDouble(),
                property("Height").toDouble()
                );
}


EllipsoidalCylinderItem::EllipsoidalCylinderItem(ParameterizedItem *parent)
    : FormFactorItem(QString("EllipsoidalCylinder"), parent)
{
    setItemName("EllipsoidalCylinder");
    setProperty("Radius_a", 8.0);
    setProperty("Radius_b", 13.0);
    setProperty("Height", 16.0);
}

IFormFactor *EllipsoidalCylinderItem::createFormFactor() const
{
    return new FormFactorEllipsoidalCylinder(
                property("Radius_a").toDouble(),
                property("Radius_b").toDouble(),
                property("Height").toDouble()
                );
}


FullSphereItem::FullSphereItem(ParameterizedItem *parent)
    : FormFactorItem(QString("FullSphere"), parent)
{
    setItemName("FullSphere");
    setProperty("Radius", 8.0);
}

IFormFactor *FullSphereItem::createFormFactor() const
{
    return new FormFactorFullSphere(
                property("Radius").toDouble()
                );
}


FullSpheroidItem::FullSpheroidItem(ParameterizedItem *parent)
    : FormFactorItem(QString("FullSpheroid"), parent)
{
    setItemName("FullSpheroid");
    setProperty("Radius", 10.0);
    setProperty("Height", 13.0);
}

IFormFactor *FullSpheroidItem::createFormFactor() const
{
    return new FormFactorFullSpheroid(
                property("Radius").toDouble(),
                property("Height").toDouble()
                );
}


HemiEllipsoidItem::HemiEllipsoidItem(ParameterizedItem *parent)
    : FormFactorItem(QString("HemiEllipsoid"), parent)
{
    setItemName("HemiEllipsoid");
    setProperty("Radius_a", 10.0);
    setProperty("Radius_b", 6.0);
    setProperty("Height", 8.0);
}

IFormFactor *HemiEllipsoidItem::createFormFactor() const
{
    return new FormFactorHemiEllipsoid(
                property("Radius_a").toDouble(),
                property("Radius_b").toDouble(),
                property("Height").toDouble()
                );
}


Prism3Item::Prism3Item(ParameterizedItem *parent)
    : FormFactorItem(QString("Prism3"), parent)
{
    setItemName("Prism3");
    setProperty("Length", 10.0);
    setProperty("Height", 13.0);
}

IFormFactor *Prism3Item::createFormFactor() const
{
    return new FormFactorPrism3(
                property("Length").toDouble(),
                property("Height").toDouble()
                );
}


Prism6Item::Prism6Item(ParameterizedItem *parent)
    : FormFactorItem(QString("Prism6"), parent)
{
    setItemName("Prism6");
    setProperty("Radius", 5.0);
    setProperty("Height", 11.0);
}

IFormFactor *Prism6Item::createFormFactor() const
{
    return new FormFactorPrism6(
                property("Radius").toDouble(),
                property("Height").toDouble()
                );
}


PyramidItem::PyramidItem(ParameterizedItem *parent)
    : FormFactorItem(QString("Pyramid"), parent)
{
    setItemName("Pyramid");
    setProperty("Length", 18.0);
    setProperty("Height", 13.0);
    setProperty("Alpha", 60.0);
}

IFormFactor *PyramidItem::createFormFactor() const
{
    return new FormFactorPyramid(
                property("Length").toDouble(),
                property("Height").toDouble(),
                property("Alpha").toDouble()*Units::degree
                );
}


Ripple1Item::Ripple1Item(ParameterizedItem *parent)
    : FormFactorItem(QString("Ripple1"), parent)
{
    setItemName("Ripple1");
    setProperty("Length", 27.0);
    setProperty("Width", 20.0);
    setProperty("Height", 14.0);
}

IFormFactor *Ripple1Item::createFormFactor() const
{
    return new FormFactorRipple1(
                property("Length").toDouble(),
                property("Width").toDouble(),
                property("Height").toDouble()
                );
}


Ripple2Item::Ripple2Item(ParameterizedItem *parent)
    : FormFactorItem(QString("Ripple2"), parent)
{
    setItemName("Ripple2");
    setProperty("Length", 36.0);
    setProperty("Width", 25.0);
    setProperty("Height", 14.0);
    setProperty("Asymmetry", 3.0);
}

IFormFactor *Ripple2Item::createFormFactor() const
{
    return new FormFactorRipple2(
                property("Length").toDouble(),
                property("Width").toDouble(),
                property("Height").toDouble(),
                property("Asymmetry").toDouble()
                );
}


TetrahedronItem::TetrahedronItem(ParameterizedItem *parent)
    : FormFactorItem(QString("Tetrahedron"), parent)
{
    setItemName("Tetrahedron");
    setProperty("Length", 15.0);
    setProperty("Height", 6.0);
    setProperty("Alpha", 60.0);
}

IFormFactor *TetrahedronItem::createFormFactor() const
{
    return new FormFactorTetrahedron(
                property("Length").toDouble(),
                property("Height").toDouble(),
                property("Alpha").toDouble()*Units::degree
                );
}


TruncatedSphereItem::TruncatedSphereItem(ParameterizedItem *parent)
    : FormFactorItem(QString("TruncatedSphere"), parent)
{
    setItemName("TruncatedSphere");
    setProperty("Radius", 5.0);
    setProperty("Height", 7.0);
}

IFormFactor *TruncatedSphereItem::createFormFactor() const
{
    return new FormFactorTruncatedSphere(
                property("Radius").toDouble(),
                property("Height").toDouble()
                );
}


TruncatedSpheroidItem::TruncatedSpheroidItem(ParameterizedItem *parent)
    : FormFactorItem(QString("TruncatedSpheroid"), parent)
{
    setItemName("TruncatedSpheroid");
    setProperty("Radius", 7.5);
    setProperty("Height", 9.0);
    setProperty("Hfc", 1.2);
}

IFormFactor *TruncatedSpheroidItem::createFormFactor() const
{
    return new FormFactorTruncatedSpheroid(
                property("Radius").toDouble(),
                property("Height").toDouble(),
                property("Hfc").toDouble()
                );
}



