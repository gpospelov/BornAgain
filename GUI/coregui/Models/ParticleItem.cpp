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
#include "Particle.h"

namespace {
const QString abundance_tooltip =
    "Proportion of this type of particles normalized to the \n"
    "total number of particles in the layout";

const QString position_tooltip =
    "Relative position of the particle's reference point \n"
    "in the coordinate system of the parent";
}

const QString ParticleItem::P_FORM_FACTOR = "Form Factor";
const QString ParticleItem::P_ABUNDANCE = QString::fromStdString(BornAgain::Abundance);
const QString ParticleItem::P_MATERIAL = "Material";
const QString ParticleItem::P_POSITION = "Position Offset";
const QString ParticleItem::T_TRANSFORMATION = "Transformation Tag";

ParticleItem::ParticleItem()
    : SessionGraphicsItem(Constants::ParticleType)
{
    addGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);
    addProperty(P_MATERIAL, MaterialUtils::getDefaultMaterialProperty().getVariant())
        ->setToolTip(QStringLiteral("Material of particle"));

    addProperty(P_ABUNDANCE, 1.0)->setLimits(RealLimits::limited(0.0, 1.0)).setDecimals(3)
        .setToolTip(abundance_tooltip);
    addGroupProperty(P_POSITION, Constants::VectorType)->setToolTip(position_tooltip);

    registerTag(T_TRANSFORMATION, 0, 1, QStringList() << Constants::TransformationType);
    setDefaultTag(T_TRANSFORMATION);

    addTranslator(PositionTranslator());
    addTranslator(RotationTranslator());

    mapper()->setOnParentChange([this](SessionItem* parentItem) {
        Q_ASSERT(parentItem == parent());
        updatePropertiesAppearance(parentItem);
    });
}

std::unique_ptr<Particle> ParticleItem::createParticle() const
{
    auto P_material = TransformToDomain::createDomainMaterial(*this);
    auto P_particle = GUIHelpers::make_unique<Particle>(*P_material);

    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    P_particle->setAbundance(abundance);

    auto& ffItem = groupItem<FormFactorItem>(ParticleItem::P_FORM_FACTOR);
    P_particle->setFormFactor(*ffItem.createFormFactor());

    TransformToDomain::setTransformationInfo(P_particle.get(), *this);

    return P_particle;
}

//! Updates enabled/disabled for particle position and particle abundance depending on context.

void ParticleItem::updatePropertiesAppearance(SessionItem* parentItem)
{
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
}

//! Returns true if this particle is a core in some CoreShellParticle
bool ParticleItem::isShellParticle()
{
    if (!parent())
        return false;

    return parent()->modelType() == Constants::ParticleCoreShellType
            && parent()->tagFromItem(this) == ParticleCoreShellItem::T_SHELL;
}

bool ParticleItem::isCoreParticle()
{
    if (!parent())
        return false;

    return parent()->modelType() == Constants::ParticleCoreShellType
            && parent()->tagFromItem(this) == ParticleCoreShellItem::T_CORE;
}
