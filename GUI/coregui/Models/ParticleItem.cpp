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
const QString ParticleItem::T_TRANSFORMATION = "Transformation Tag";

ParticleItem::ParticleItem()
    : SessionGraphicsItem(Constants::ParticleType)
{
    addGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);
    addProperty(P_MATERIAL,
                     MaterialUtils::getDefaultMaterialProperty().getVariant());
    addProperty(P_ABUNDANCE, 1.0)->setLimits(AttLimits::limited(0.0, 1.0));
    getItem(P_ABUNDANCE)->setDecimals(3);
    addGroupProperty(P_POSITION, Constants::VectorType);
    PositionTranslator position_translator;
    ModelPath::addParameterTranslator(position_translator);

    registerTag(T_TRANSFORMATION, 0, 1, QStringList() << Constants::TransformationType);
    setDefaultTag(T_TRANSFORMATION);
    RotationTranslator rotation_translator;
    ModelPath::addParameterTranslator(rotation_translator);

    mapper()->setOnParentChange(
                [this](SessionItem* parentItem) {
        if (parentItem) {
            if (parent()->modelType() == Constants::ParticleCoreShellType
                || parent()->modelType() == Constants::ParticleCompositionType
                || parent()->modelType() == Constants::ParticleDistributionType) {
                setItemValue(ParticleItem::P_ABUNDANCE, 1.0);
                getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
                if (parent()->modelType() == Constants::ParticleCoreShellType &&
                    parent()->tagFromItem(this) == ParticleCoreShellItem::T_SHELL) {
                        SessionItem *p_position_item = getGroupItem(ParticleItem::P_POSITION);
                    p_position_item->setItemValue(VectorItem::P_X, 0.0);
                    p_position_item->setItemValue(VectorItem::P_Y, 0.0);
                    p_position_item->setItemValue(VectorItem::P_Z, 0.0);
                    getItem(ParticleItem::P_POSITION)->setEnabled(false);
                } else {
                    getItem(ParticleItem::P_POSITION)->setEnabled(true);
                }
                return;
            }
        }
        getItem(ParticleItem::P_ABUNDANCE)->setEnabled(true);
        getItem(ParticleItem::P_POSITION)->setEnabled(true);
    });
}

std::unique_ptr<Particle> ParticleItem::createParticle() const
{
    auto P_material = TransformToDomain::createDomainMaterial(*this);
    auto P_particle = GUIHelpers::make_unique<Particle>(*P_material);

    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    P_particle->setAbundance(abundance);

    auto ffItem = static_cast<FormFactorItem*>(getGroupItem(ParticleItem::P_FORM_FACTOR));
    Q_ASSERT(ffItem);
    auto P_ff = ffItem->createFormFactor();
    P_particle->setFormFactor(*P_ff);

    TransformToDomain::setTransformationInfo(P_particle.get(), *this);

    return P_particle;
}
