// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformationItem.cpp
//! @brief     Implements class TransformationItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "TransformationItem.h"

const QString TransformationItem::P_ROT = "Rotation type";


TransformationItem::TransformationItem()
    : SessionGraphicsItem(Constants::TransformationType)
{
    setToolTip(QStringLiteral("Rotation applied to particles"));
    addGroupProperty(P_ROT, Constants::RotationGroup );
}
