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
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MesoCrystalItem.h"
#include "ComboProperty.h"
#include "ModelPath.h"
#include "BornAgainNamespace.h"

namespace {
const QString abundance_tooltip =
    "Proportion of this type of particles normalized to the \n"
    "total number of particles in the layout";

const QString lattice_vector1_tooltip =
    "Coordinates of the first lattice vector";

const QString lattice_vector2_tooltip =
    "Coordinates of the second lattice vector";

const QString lattice_vector3_tooltip =
    "Coordinates of the third lattice vector";

const QString position_tooltip =
    "Relative position of the particle's reference point \n"
    "in the coordinate system of the parent";

const QString density_tooltip =
    "Number of particles per square nanometer (particle surface density).\n "
    "Should be defined for disordered and 1d-ordered particle collections.";
}

const QString MesoCrystalItem::P_FORM_FACTOR = "Outer Shape";
const QString MesoCrystalItem::P_ABUNDANCE = QString::fromStdString(BornAgain::Abundance);
const QString MesoCrystalItem::T_BASIS_PARTICLE = "Basis Particle";
const QString MesoCrystalItem::P_LATTICE = "Lattice";
const QString MesoCrystalItem::P_VECTOR_1 = "First lattice vector";
const QString MesoCrystalItem::P_VECTOR_2 = "Second lattice vector";
const QString MesoCrystalItem::P_VECTOR_3 = "Third lattice vector";
const QString MesoCrystalItem::P_POSITION = "Position Offset";
const QString MesoCrystalItem::T_TRANSFORMATION = "Transformation Tag";


MesoCrystalItem::MesoCrystalItem() : SessionGraphicsItem(Constants::MesoCrystalType)
{
    setToolTip(QStringLiteral("A 3D crystal structure of nanoparticles"));

    addGroupProperty(P_FORM_FACTOR, Constants::FormFactorGroup);

    addProperty(P_ABUNDANCE, 1.0)->setLimits(RealLimits::limited(0.0, 1.0)).setDecimals(3)
        .setToolTip(abundance_tooltip);

    addGroupProperty(P_VECTOR_1, Constants::VectorType)->setToolTip(lattice_vector1_tooltip);
    addGroupProperty(P_VECTOR_2, Constants::VectorType)->setToolTip(lattice_vector2_tooltip);
    addGroupProperty(P_VECTOR_3, Constants::VectorType)->setToolTip(lattice_vector3_tooltip);
    addGroupProperty(P_POSITION, Constants::VectorType)->setToolTip(position_tooltip);

    registerTag(T_BASIS_PARTICLE, 0, 1, QStringList() << Constants::ParticleType
                                                      << Constants::ParticleCoreShellType
                                                      << Constants::ParticleCompositionType);
    setDefaultTag(T_BASIS_PARTICLE);

    registerTag(T_TRANSFORMATION, 0, 1, QStringList() << Constants::TransformationType);

    addTranslator(PositionTranslator());
    addTranslator(RotationTranslator());
}
