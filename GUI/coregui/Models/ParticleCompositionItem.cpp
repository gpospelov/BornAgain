// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParticleCompositionItem.cpp
//! @brief     Implements class ParticleCompositionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCompositionItem.h"
#include "ParticleCoreShellItem.h"
#include "ParticleItem.h"
#include "TransformToDomain.h"
#include "GUIHelpers.h"
#include "ModelPath.h"

const QString ParticleCompositionItem::T_PARTICLES = "Particle Tag";
const QString ParticleCompositionItem::T_TRANSFORMATION = "Transformation Tag";

ParticleCompositionItem::ParticleCompositionItem()
    : SessionGraphicsItem(Constants::ParticleCompositionType)
{
    registerProperty(ParticleItem::P_ABUNDANCE, 1.0);
    getItem(ParticleItem::P_ABUNDANCE)->setLimits(AttLimits::limited(0.0, 1.0));
    getItem(ParticleItem::P_ABUNDANCE)->setDecimals(3);
    registerGroupProperty(ParticleItem::P_POSITION, Constants::VectorType);
    PositionTranslator position_translator;
    ModelPath::addParameterTranslator(position_translator);

    registerTag(T_PARTICLES, 0, -1, QStringList() << Constants::ParticleType <<
                Constants::ParticleCoreShellType << Constants::ParticleCompositionType);
    setDefaultTag(T_PARTICLES);
    registerTag(T_TRANSFORMATION, 0, 1, QStringList() << Constants::TransformationType);
    RotationTranslator rotation_translator;
    ModelPath::addParameterTranslator(rotation_translator);

    mapper()->setOnParentChange(
                [this](SessionItem *parent) {
        if (parent && (parent->modelType() == Constants::ParticleCompositionType
            || parent->modelType() == Constants::ParticleDistributionType)) {
            setRegisteredProperty(ParticleItem::P_ABUNDANCE, 1.0);
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
        } else {
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(true);
        }
    });
}

std::unique_ptr<ParticleComposition> ParticleCompositionItem::createParticleComposition() const
{
    double abundance = getRegisteredProperty(ParticleItem::P_ABUNDANCE).toDouble();
    auto P_composition = GUIHelpers::make_unique<ParticleComposition>();
    P_composition->setAbundance(abundance);
    QVector<SessionItem *> children = childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleType) {
            auto *particle_item = static_cast<ParticleItem*>(children[i]);
            auto P_particle = particle_item->createParticle();
            if (P_particle) {
                P_composition->addParticle(*P_particle);
            }
        } else if (children[i]->modelType() == Constants::ParticleCoreShellType) {
            auto *particle_coreshell_item = static_cast<ParticleCoreShellItem*>(children[i]);
            auto P_particle_coreshell = particle_coreshell_item->createParticleCoreShell();
            if (P_particle_coreshell) {
                P_composition->addParticle(*P_particle_coreshell);
            }
        } else if (children[i]->modelType() == Constants::ParticleCompositionType) {
            auto *particlecomposition_item = static_cast<ParticleCompositionItem*>(children[i]);
            auto P_child_composition = particlecomposition_item->createParticleComposition();
            if (P_child_composition) {
                P_composition->addParticle(*P_child_composition);
            }
        } else if (children[i]->modelType() == Constants::TransformationType) {
            continue;
        } else {
//            throw GUIHelpers::Error("ParticleCompositionItem::createParticleComposition()"
//                                    " -> Error! Not implemented");
        }
    }
    TransformToDomain::setTransformationInfo(P_composition.get(), *this);

    return P_composition;
}
