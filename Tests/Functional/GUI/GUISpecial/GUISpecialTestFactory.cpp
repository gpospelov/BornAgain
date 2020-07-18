// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/GUISpecialTestFactory.cpp
//! @brief     Implements GUISpecialTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/GUI/GUISpecial/GUISpecialTestFactory.h"
#include "Tests/Functional/GUI/GUISpecial/GUISaveLoadProject.h"
#include "Tests/Functional/GUI/GUISpecial/TranslationCases.h"

GUISpecialTestFactory::GUISpecialTestFactory()
{
    registerItem("BasicTranslation", create_new<BasicTranslationTest>);

    registerItem("RadialParaTranslation", create_new<RadialParaTranslationTest>);

    registerItem("HardDiskTranslation", create_new<HardDiskTranslationTest>);

    registerItem("HexParaTranslation", create_new<HexParaTranslationTest>);

    registerItem("CoreShellTranslation", create_new<CoreShellTranslationTest>);

    registerItem("RoughnessTranslation", create_new<RoughnessTranslationTest>);

    registerItem("SquareLatticeTranslation", create_new<SquareLatticeTranslationTest>);

    registerItem("RotationTranslation", create_new<RotationTranslationTest>);

    registerItem("SizeDistributionTranslation", create_new<SizeDistributionTranslationTest>);

    registerItem("CompositionTranslation", create_new<CompositionTranslationTest>);

    registerItem("Para2DTranslation", create_new<Para2DTranslationTest>);

    registerItem("Lattice1DTranslation", create_new<Lattice1DTranslationTest>);

    registerItem("Lattice2DTranslation", create_new<Lattice2DTranslationTest>);

    registerItem("TwoLayerRoughnessTranslation", create_new<TwoLayerRoughnessTranslationTest>);

    registerItem("MesoCrystalTranslation", create_new<MesoCrystalTranslationTest>);

    registerItem("MagneticSpheresTranslation", create_new<MagneticSpheresTranslationTest>);

    registerItem("SaveLoadProject", create_new<GUISaveLoadProject>);
}
