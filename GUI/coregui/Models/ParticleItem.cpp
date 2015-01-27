// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleItem.cpp
//! @brief     Implements class ParticleItem
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "MaterialUtils.h"
#include <QDebug>

const QString ParticleItem::P_FORM_FACTOR = "Form Factor";
const QString ParticleItem::P_DEPTH = "Depth";
const QString ParticleItem::P_ABUNDANCE = "Abundance";
const QString ParticleItem::P_MATERIAL = "Material";


ParticleItem::ParticleItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleType, parent)
{
    setItemName(Constants::ParticleType);
    setItemPort(ParameterizedItem::PortInfo::PORT_0);
    registerGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);
    registerProperty(P_MATERIAL,
                     MaterialUtils::getDefaultMaterialProperty().getVariant());
    registerProperty(P_DEPTH, 0.0);
    registerProperty(P_ABUNDANCE, 1.0,
                     PropertyAttribute(AttLimits::limited(0.0, 1.0),3));

    addToValidChildren(Constants::TransformationType, PortInfo::PORT_0, 1);

    setPropertyAppearance(ParameterizedItem::P_NAME,
                          PropertyAttribute::VISIBLE);
}

