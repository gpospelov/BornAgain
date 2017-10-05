// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MesoCrystalItem.cpp
//! @brief     Implements class MesoCrystalItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke, Dmitry Yurov
//
// ************************************************************************** //

#include "MesoCrystalItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "Crystal.h"
#include "FormFactorItems.h"
#include "GUIHelpers.h"
#include "MesoCrystal.h"
#include "ModelPath.h"
#include "Particle.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShell.h"
#include "ParticleCoreShellItem.h"
#include "ParticleItem.h"
#include "TransformToDomain.h"
#include "VectorItem.h"

namespace {
const QString abundance_tooltip =
    "Proportion of this type of mesocrystal normalized to the \n"
    "total number of particles in the layout";

const QString lattice_vector1_tooltip =
    "Coordinates of the first lattice vector";

const QString lattice_vector2_tooltip =
    "Coordinates of the second lattice vector";

const QString lattice_vector3_tooltip =
    "Coordinates of the third lattice vector";

const QString position_tooltip =
    "Relative position of the mesocrystal's reference point \n"
    "in the coordinate system of the parent";

const QString density_tooltip =
    "Number of mesocrystals per square nanometer (particle surface density).\n "
    "Should be defined for disordered and 1d-ordered particle collections.";

bool IsIParticleName(QString name);
}

const QString MesoCrystalItem::P_FORM_FACTOR = "Outer Shape";
const QString MesoCrystalItem::T_BASIS_PARTICLE = "Basis Particle";
const QString MesoCrystalItem::P_VECTOR_A = "First lattice vector";
const QString MesoCrystalItem::P_VECTOR_B = "Second lattice vector";
const QString MesoCrystalItem::P_VECTOR_C = "Third lattice vector";


MesoCrystalItem::MesoCrystalItem() : SessionGraphicsItem(Constants::MesoCrystalType)
{
    setToolTip(QStringLiteral("A 3D crystal structure of nanoparticles"));

    addGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);

    addProperty(ParticleItem::P_ABUNDANCE, 1.0)->setLimits(RealLimits::limited(0.0, 1.0)).setDecimals(3)
        .setToolTip(abundance_tooltip);

    addGroupProperty(P_VECTOR_A, Constants::VectorType)->setToolTip(lattice_vector1_tooltip);
    addGroupProperty(P_VECTOR_B, Constants::VectorType)->setToolTip(lattice_vector2_tooltip);
    addGroupProperty(P_VECTOR_C, Constants::VectorType)->setToolTip(lattice_vector3_tooltip);
    addGroupProperty(ParticleItem::P_POSITION, Constants::VectorType)->setToolTip(position_tooltip);

    registerTag(T_BASIS_PARTICLE, 0, 1, QStringList() << Constants::ParticleType
                                                      << Constants::ParticleCoreShellType
                                                      << Constants::ParticleCompositionType
                                                      << Constants::MesoCrystalType);
    setDefaultTag(T_BASIS_PARTICLE);

    registerTag(ParticleItem::T_TRANSFORMATION, 0, 1,
                QStringList() << Constants::TransformationType);

    addTranslator(PositionTranslator());
    addTranslator(RotationTranslator());
//    addTranslator(MesoCrystalTranslator());

    mapper()->setOnParentChange(
                [this](SessionItem *parent) {
        if (parent && parent->modelType() != Constants::ParticleLayoutType) {
            setItemValue(ParticleItem::P_ABUNDANCE, 1.0);
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(false);
        } else {
            getItem(ParticleItem::P_ABUNDANCE)->setEnabled(true);
        }
    });
}

std::unique_ptr<MesoCrystal> MesoCrystalItem::createMesoCrystal() const
{
    auto lattice = getLattice();
    if (!(lattice.volume()>0.0)) {
        throw GUIHelpers::Error("MesoCrystalItem::createMesoCrystal(): "
                                "Lattice volume not strictly positive");
    }
    auto P_basis = getBasis();
    if (!P_basis) {
        throw GUIHelpers::Error("MesoCrystalItem::createMesoCrystal(): "
                                "No basis particle defined");
    }
    Crystal crystal(*P_basis, lattice);

    auto P_ff = getOuterShape();
    if (!P_ff) {
        throw GUIHelpers::Error("MesoCrystalItem::createMesoCrystal(): "
                                "No outer shape defined");
    }

    auto P_result = GUIHelpers::make_unique<MesoCrystal>(crystal, *P_ff);
    TransformToDomain::setTransformationInfo(P_result.get(), *this);

    return P_result;
}

QStringList MesoCrystalItem::translateList(const QStringList& list) const
{
    QStringList result = list;
    // Add CrystalType to path name of basis particle
    if (IsIParticleName(list.back())) {
        result << QString::fromStdString(BornAgain::CrystalType);
    }
    result = SessionItem::translateList(result);
    return result;
}

Lattice MesoCrystalItem::getLattice() const
{
    SessionItem* lattice_vector1_item = getItem(P_VECTOR_A);
    SessionItem* lattice_vector2_item = getItem(P_VECTOR_B);
    SessionItem* lattice_vector3_item = getItem(P_VECTOR_C);
    kvector_t a1(lattice_vector1_item->getItemValue(VectorItem::P_X).toDouble(),
                 lattice_vector1_item->getItemValue(VectorItem::P_Y).toDouble(),
                 lattice_vector1_item->getItemValue(VectorItem::P_Z).toDouble());
    kvector_t a2(lattice_vector2_item->getItemValue(VectorItem::P_X).toDouble(),
                 lattice_vector2_item->getItemValue(VectorItem::P_Y).toDouble(),
                 lattice_vector2_item->getItemValue(VectorItem::P_Z).toDouble());
    kvector_t a3(lattice_vector3_item->getItemValue(VectorItem::P_X).toDouble(),
                 lattice_vector3_item->getItemValue(VectorItem::P_Y).toDouble(),
                 lattice_vector3_item->getItemValue(VectorItem::P_Z).toDouble());
    return Lattice(a1, a2, a3);
}

std::unique_ptr<IParticle> MesoCrystalItem::getBasis() const
{
    QVector<SessionItem *> children = childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleType) {
            auto *particle_item = static_cast<ParticleItem*>(children[i]);
            return particle_item->createParticle();
        } else if (children[i]->modelType() == Constants::ParticleCoreShellType) {
            auto *particle_coreshell_item = static_cast<ParticleCoreShellItem*>(children[i]);
            return particle_coreshell_item->createParticleCoreShell();
        } else if (children[i]->modelType() == Constants::ParticleCompositionType) {
            auto *particlecomposition_item = static_cast<ParticleCompositionItem*>(children[i]);
            return particlecomposition_item->createParticleComposition();
        } else if (children[i]->modelType() == Constants::MesoCrystalType) {
            auto *mesocrystal_item = static_cast<MesoCrystalItem*>(children[i]);
            return mesocrystal_item->createMesoCrystal();
        }
    }
    return {};
}

std::unique_ptr<IFormFactor> MesoCrystalItem::getOuterShape() const
{
    auto& ff_item = groupItem<FormFactorItem>(MesoCrystalItem::P_FORM_FACTOR);
    return ff_item.createFormFactor();
}

namespace {
bool IsIParticleName(QString name) {
    return (name.startsWith(Constants::ParticleType)
         || name.startsWith(Constants::ParticleCompositionType)
         || name.startsWith(Constants::ParticleCoreShellType)
         || name.startsWith(Constants::MesoCrystalType));
}
}
