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
#include "ParticleCoreShellItem.h"
#include "FormFactorItems.h"
#include "MaterialUtils.h"
#include "VectorItem.h"
#include "TransformToDomain.h"
#include "GUIHelpers.h"
#include "ModelPath.h"

#include <QDebug>

const QString ParticleItem::P_FORM_FACTOR = "Form Factor";
const QString ParticleItem::P_ABUNDANCE = "Abundance";
const QString ParticleItem::P_MATERIAL = "Material";
const QString ParticleItem::P_POSITION = "Position Offset";

ParticleItem::ParticleItem()
    : ParameterizedGraphicsItem(Constants::ParticleType)
{
    registerGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);
    registerProperty(P_MATERIAL,
                     MaterialUtils::getDefaultMaterialProperty().getVariant());
    registerProperty(P_ABUNDANCE, 1.0).limited(0.0, 1.0).setDecimals(3);
    registerGroupProperty(P_POSITION, Constants::VectorType);
    PositionTranslator position_translator;
    ModelPath::addParameterTranslator(position_translator);

    addToValidChildren(Constants::TransformationType, PortInfo::PORT_0, 1);
    RotationTranslator rotation_translator;
    ModelPath::addParameterTranslator(rotation_translator);
}

void ParticleItem::insertChildItem(int row, ParameterizedItem *item)
{
    ParameterizedItem::insertChildItem(row, item);
    if (item->modelType() == Constants::TransformationType) {
        int port = int(item->port());
//        int port = item->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT).toInt();
        if (port == PortInfo::DEFAULT) {
            item->setPort(PortInfo::PORT_0);
        }
    }
}

void ParticleItem::onPropertyChange(const QString &name)
{
    ParameterizedItem::onPropertyChange(name);
    if (name == "OBSOLETE_P_PORT" && parent()) {
        if (parent()->modelType() == Constants::ParticleCoreShellType
            || parent()->modelType() == Constants::ParticleCompositionType
            || parent()->modelType() == Constants::ParticleDistributionType) {
            setRegisteredProperty(ParticleItem::P_ABUNDANCE, 1.0);
            getPropertyAttribute(ParticleItem::P_ABUNDANCE).setDisabled();
//            int port = getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT).toInt();
            int port = int(this->port());
            if (parent()->modelType() == Constants::ParticleCoreShellType) {
                auto p_coreshell = static_cast<ParticleCoreShellItem*>(parent());
                p_coreshell->notifyChildParticlePortChanged();
                if (port == PortInfo::PORT_1) {
                    ParameterizedItem *p_position_item = getGroupItem(ParticleItem::P_POSITION);
                    p_position_item->setRegisteredProperty(VectorItem::P_X, 0.0);
                    p_position_item->setRegisteredProperty(VectorItem::P_Y, 0.0);
                    p_position_item->setRegisteredProperty(VectorItem::P_Z, 0.0);
                    getPropertyAttribute(ParticleItem::P_POSITION).setDisabled();
                }
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

    auto ffItem = static_cast<FormFactorItem*>(getGroupItem(ParticleItem::P_FORM_FACTOR));
    Q_ASSERT(ffItem);
    auto P_ff = ffItem->createFormFactor();
    P_particle->setFormFactor(*P_ff);

    TransformToDomain::setTransformationInfo(P_particle.get(), *this);

    return P_particle;
}
