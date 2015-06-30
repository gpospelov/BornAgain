// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleItem.cpp
//! @brief     Implements class ParticleItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "MaterialUtils.h"
#include <QDebug>

const QString ParticleItem::P_FORM_FACTOR = "Form Factor";
const QString ParticleItem::P_ABUNDANCE = "Abundance";
const QString ParticleItem::P_MATERIAL = "Material";
const QString ParticleItem::P_POSITION = "Position Offset";

ParticleItem::ParticleItem(ParameterizedItem *parent)
    : ParameterizedGraphicsItem(Constants::ParticleType, parent)
{
    setItemName(Constants::ParticleType);

    registerGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);
    registerProperty(P_MATERIAL,
                     MaterialUtils::getDefaultMaterialProperty().getVariant());
    registerProperty(P_ABUNDANCE, 1.0,
                     PropertyAttribute(AttLimits::limited(0.0, 1.0),3));
    registerGroupProperty(P_POSITION, Constants::VectorType);

    addToValidChildren(Constants::TransformationType, PortInfo::PORT_0, 1);
    setPropertyAppearance(ParameterizedItem::P_NAME,
                          PropertyAttribute::VISIBLE);
}

void ParticleItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    if (item->modelType() == Constants::TransformationType) {
        int port = item->getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
        if (port == PortInfo::DEFAULT) {
            item->setItemPort(PortInfo::PORT_0);
        }
    }
}

