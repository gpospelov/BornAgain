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


AnisoPyramidItem::AnisoPyramidItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("AnisoPyramid"), parent)
{
    setItemName("AnisoPyramid");
    setProperty("Length", 20.0);
    setProperty("Width", 16.0);
    setProperty("Height", 13.0);
    setProperty("Alpha", 60.0);
}


BoxItem::BoxItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Box"), parent)
{
    setItemName("Box");
    setProperty("Length", 20.0);
    setProperty("Width", 16.0);
    setProperty("Height", 13.0);
}


ConeItem::ConeItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Cone"), parent)
{
    setItemName("Cone");
    setProperty("Radius", 10.0);
    setProperty("Height", 13.0);
    setProperty("Alpha", 60.0);
}


Cone6Item::Cone6Item(ParameterizedItem *parent)
    : ParameterizedItem(QString("Cone6"), parent)
{
    setItemName("Cone6");
    setProperty("Radius", 10.0);
    setProperty("Height", 13.0);
    setProperty("Alpha", 60.0);
}


CuboctahedronItem::CuboctahedronItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Cuboctahedron"), parent)
{
    setItemName("Cuboctahedron");
    setProperty("Length", 20.0);
    setProperty("Height", 13.0);
    setProperty("HeightRatio", 0.7);
    setProperty("Alpha", 60.0);
}


CylinderItem::CylinderItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Cylinder"), parent)
{
    setItemName("Cylinder");
    setProperty("Radius", 8.0);
    setProperty("Height", 16.0);
}


EllipsoidalCylinderItem::EllipsoidalCylinderItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("EllipsoidalCylinder"), parent)
{
    setItemName("EllipsoidalCylinder");
    setProperty("Radius_a", 8.0);
    setProperty("Radius_b", 13.0);
    setProperty("Height", 16.0);
}


FullSphereItem::FullSphereItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("FullSphere"), parent)
{
    setItemName("FullSphere");
    setProperty("Radius", 8.0);
}


FullSpheroidItem::FullSpheroidItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("FullSpheroid"), parent)
{
    setItemName("FullSpheroid");
    setProperty("Radius", 10.0);
    setProperty("Height", 13.0);
}


HemiEllipsoidItem::HemiEllipsoidItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("HemiEllipsoid"), parent)
{
    setItemName("HemiEllipsoid");
    setProperty("Radius_a", 10.0);
    setProperty("Radius_b", 6.0);
    setProperty("Height", 8.0);
}


Prism3Item::Prism3Item(ParameterizedItem *parent)
    : ParameterizedItem(QString("Prism3"), parent)
{
    setItemName("Prism3");
    setProperty("Length", 10.0);
    setProperty("Height", 13.0);
}


Prism6Item::Prism6Item(ParameterizedItem *parent)
    : ParameterizedItem(QString("Prism6"), parent)
{
    setItemName("Prism6");
    setProperty("Radius", 5.0);
    setProperty("Height", 11.0);
}


PyramidItem::PyramidItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Pyramid"), parent)
{
    setItemName("Pyramid");
    setProperty("Length", 18.0);
    setProperty("Height", 13.0);
    setProperty("Alpha", 60.0);
}


Ripple1Item::Ripple1Item(ParameterizedItem *parent)
    : ParameterizedItem(QString("Ripple1"), parent)
{
    setItemName("Ripple1");
    setProperty("Length", 27.0);
    setProperty("Width", 20.0);
    setProperty("Height", 14.0);
}


Ripple2Item::Ripple2Item(ParameterizedItem *parent)
    : ParameterizedItem(QString("Ripple2"), parent)
{
    setItemName("Ripple2");
    setProperty("Length", 36.0);
    setProperty("Width", 25.0);
    setProperty("Height", 14.0);
    setProperty("Displace", 3.0);
}


TetrahedronItem::TetrahedronItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Tetrahedron"), parent)
{
    setItemName("Tetrahedron");
    setProperty("Length", 15.0);
    setProperty("Height", 6.0);
    setProperty("Alpha", 60.0);
}


TruncatedSphereItem::TruncatedSphereItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("TruncatedSphere"), parent)
{
    setItemName("TruncatedSphere");
    setProperty("Radius", 5.0);
    setProperty("Height", 7.0);
}


TruncatedSpheroidItem::TruncatedSpheroidItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("TruncatedSpheroid"), parent)
{
    setItemName("TruncatedSpheroid");
    setProperty("Radius", 7.5);
    setProperty("Height", 9.0);
    setProperty("Hfc", 1.2);
}



