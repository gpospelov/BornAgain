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

#include "CylinderItem.h"

CylinderItem::CylinderItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("Cylinder"), parent)
{
    setItemName("CylinderName");
    setProperty("Radius", 1.0);
    setProperty("Height", 1.0);
}

CylinderItem::~CylinderItem()
{
}
