//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/VectorItem.cpp
//! @brief     Implements class VectorItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/VectorItem.h"

const QString VectorItem::P_X = "X";
const QString VectorItem::P_Y = "Y";
const QString VectorItem::P_Z = "Z";

VectorItem::VectorItem() : SessionItem("Vector")
{
    addProperty(P_X, 0.0)->setLimits(RealLimits::limitless()).setToolTip("x-coordinate");
    addProperty(P_Y, 0.0)->setLimits(RealLimits::limitless()).setToolTip("y-coordinate");
    addProperty(P_Z, 0.0)->setLimits(RealLimits::limitless()).setToolTip("z-coordinate");

    mapper()->setOnPropertyChange([this](const QString&) { updateLabel(); });

    updateLabel();
    setEditable(false);
}

double VectorItem::x() const
{
    return getItemValue(P_X).toDouble();
}

void VectorItem::setX(double value)
{
    setItemValue(P_X, value);
}

double VectorItem::y() const
{
    return getItemValue(P_Y).toDouble();
}

void VectorItem::setY(double value)
{
    setItemValue(P_Y, value);
}

double VectorItem::z() const
{
    return getItemValue(P_Z).toDouble();
}

void VectorItem::setZ(double value)
{
    setItemValue(P_Z, value);
}

void VectorItem::setXYZ(double x_value, double y_value, double z_value)
{
    setX(x_value);
    setY(y_value);
    setZ(z_value);
}

kvector_t VectorItem::getVector() const
{
    return kvector_t(x(), y(), z());
}

void VectorItem::setVector(const kvector_t& vec)
{
    setXYZ(vec.x(), vec.y(), vec.z());
}

void VectorItem::updateLabel()
{
    QString label = QString("(%1, %2, %3)").arg(x()).arg(y()).arg(z());

    setValue(label);
}
