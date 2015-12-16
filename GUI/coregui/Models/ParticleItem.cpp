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
#include "VectorItem.h"
#include "TransformToDomain.h"
#include "GUIHelpers.h"

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

void ParticleItem::onPropertyChange(const QString &name)
{
    ParameterizedItem::onPropertyChange(name);
    if (name == P_PORT && parent()) {
        if (parent()->modelType() == Constants::ParticleCoreShellType
            || parent()->modelType() == Constants::ParticleCompositionType
            || parent()->modelType() == Constants::ParticleDistributionType) {
            setRegisteredProperty(ParticleItem::P_ABUNDANCE, 1.0);
            setPropertyAppearance(ParticleItem::P_ABUNDANCE, PropertyAttribute::DISABLED);
            int port = getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
            if (parent()->modelType() == Constants::ParticleCoreShellType
                && port == PortInfo::PORT_1) {
                ParameterizedItem *p_position_item = getSubItems()[ParticleItem::P_POSITION];
                p_position_item->setRegisteredProperty(VectorItem::P_X, 0.0);
                p_position_item->setRegisteredProperty(VectorItem::P_Y, 0.0);
                p_position_item->setRegisteredProperty(VectorItem::P_Z, 0.0);
                setPropertyAppearance(ParticleItem::P_POSITION, PropertyAttribute::DISABLED);
            }
        }
    }
}

std::unique_ptr<Particle> ParticleItem::createParticle() const
{
    auto P_material = TransformToDomain::createDomainMaterial(*this);
    auto P_particle = GUIHelpers::make_unique<Particle>(*P_material);

    double abundance = getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    P_particle->setAbundance(abundance);

    auto ffItem = getSubItems()[ParticleItem::P_FORM_FACTOR];
    Q_ASSERT(ffItem);
    auto P_ff = TransformToDomain::createFormFactor(*ffItem);
    P_particle->setFormFactor(*P_ff);

    return P_particle;
}
