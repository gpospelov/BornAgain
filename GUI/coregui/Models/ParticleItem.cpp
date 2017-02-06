// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleItem.cpp
//! @brief     Implements class ParticleItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "GUIHelpers.h"
#include "MaterialUtils.h"
#include "ModelPath.h"
#include "ParticleCoreShellItem.h"
#include "TransformToDomain.h"
#include "VectorItem.h"


const QString ParticleItem::P_FORM_FACTOR = "Form Factor";
const QString ParticleItem::P_ABUNDANCE = QString::fromStdString(BornAgain::Abundance);
const QString ParticleItem::P_MATERIAL = "Material";
const QString ParticleItem::P_POSITION = "Position Offset";
const QString ParticleItem::T_TRANSFORMATION = "Transformation Tag";

ParticleItem::ParticleItem()
    : SessionGraphicsItem(Constants::ParticleType)
{
    addGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);
    addProperty(P_MATERIAL,
                     MaterialUtils::getDefaultMaterialProperty().getVariant());
    addProperty(P_ABUNDANCE, 1.0)->setLimits(RealLimits::limited(0.0, 1.0));
    getItem(P_ABUNDANCE)->setDecimals(3);
    addGroupProperty(P_POSITION, Constants::VectorType);

    registerTag(T_TRANSFORMATION, 0, 1, QStringList() << Constants::TransformationType);
    setDefaultTag(T_TRANSFORMATION);

    addTranslator(PositionTranslator());
    addTranslator(RotationTranslator());

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
                        SessionItem *positionItem = getItem(ParticleItem::P_POSITION);
                    positionItem->setItemValue(VectorItem::P_X, 0.0);
                    positionItem->setItemValue(VectorItem::P_Y, 0.0);
                    positionItem->setItemValue(VectorItem::P_Z, 0.0);
                    positionItem->setEnabled(false);
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
