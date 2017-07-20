// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParticleCoreShellItem.cpp
//! @brief     Implements class ParticleCoreShellItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParticleCoreShellItem.h"
#include "GUIHelpers.h"
#include "ModelPath.h"
#include "ParticleItem.h"
#include "TransformToDomain.h"
#include "Particle.h"
#include "ParticleCoreShell.h"

namespace {
const QString abundance_tooltip =
    "Proportion of this type of particles normalized to the \n"
    "total number of particles in the layout";

const QString position_tooltip =
    "Relative position of the particle's reference point \n"
    "in the coordinate system of the parent";
}

const QString ParticleCoreShellItem::T_CORE = "Core Tag";
const QString ParticleCoreShellItem::T_SHELL = "Shell Tag";

// TODO make ParticleCoreShellItem and ParticleItem to derive from common base.

ParticleCoreShellItem::ParticleCoreShellItem()
    : SessionGraphicsItem(Constants::ParticleCoreShellType)
{
    setToolTip(QStringLiteral("A particle with a core/shell geometry"));

    addProperty(ParticleItem::P_ABUNDANCE, 1.0)->setLimits(RealLimits::limited(0.0, 1.0))
        .setDecimals(3).setToolTip(abundance_tooltip);

    addGroupProperty(ParticleItem::P_POSITION, Constants::VectorType)->setToolTip(position_tooltip);

    registerTag(T_CORE, 0, 1, QStringList() << Constants::ParticleType);
    registerTag(T_SHELL, 0, 1, QStringList() << Constants::ParticleType);
    registerTag(ParticleItem::T_TRANSFORMATION, 0, 1, QStringList() << Constants::TransformationType);

    addTranslator(PositionTranslator());
    addTranslator(RotationTranslator());

    mapper()->setOnParentChange(
                [this](SessionItem* newParent)
    {
        if (newParent) {
            if (parent()->modelType() == Constants::ParticleCompositionType
                || parent()->modelType() == Constants::ParticleDistributionType) {
                setItemValue(ParticleItem::P_ABUNDANCE, 1.0);
                getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
            }
        } else {
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(true);
        }
    });

}

std::unique_ptr<ParticleCoreShell> ParticleCoreShellItem::createParticleCoreShell() const
{
    double abundance = getItemValue(ParticleItem::P_ABUNDANCE).toDouble();
    auto children = childItems();
    std::unique_ptr<Particle> P_core {};
    std::unique_ptr<Particle> P_shell {};
    auto core_item = dynamic_cast<ParticleItem*>(getItem(T_CORE));
    if (core_item)
        P_core = core_item->createParticle();
    auto shell_item = dynamic_cast<ParticleItem*>(getItem(T_SHELL));
    if (shell_item)
        P_shell = shell_item->createParticle();
    if (!P_core || !P_shell)
        throw GUIHelpers::Error("ParticleCoreShellItem::createParticleCoreShell -> Error. Either "
                                "core or shell particle is undefined.");
    auto P_coreshell = GUIHelpers::make_unique<ParticleCoreShell>(*P_shell, *P_core);
    P_coreshell->setAbundance(abundance);
    TransformToDomain::setTransformationInfo(P_coreshell.get(), *this);
    return P_coreshell;
}
