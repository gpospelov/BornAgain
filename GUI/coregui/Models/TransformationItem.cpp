// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformationItem.cpp
//! @brief     Implements class TransformationItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TransformationItem.h"
#include "ParticleItem.h"
#include "GUIHelpers.h"
#include <QDebug>

const QString TransformationItem::P_ROT = "Rotation type";


TransformationItem::TransformationItem()
    : SessionGraphicsItem(Constants::TransformationType)
{
    registerGroupProperty(P_ROT, Constants::RotationGroup );
}
