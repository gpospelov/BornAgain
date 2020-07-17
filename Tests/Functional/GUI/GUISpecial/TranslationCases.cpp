// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/TranslationCases.cpp
//! @brief     Defines classes from TranslationCases family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/GUI/GUISpecial/TranslationCases.h"

BasicTranslationTest::BasicTranslationTest()
    : GUITranslationTest("BasicGISAS", "CylindersAndPrismsBuilder")
{
}

RadialParaTranslationTest::RadialParaTranslationTest()
    : GUITranslationTest("BasicGISAS", "RadialParaCrystalBuilder")
{
}

HardDiskTranslationTest::HardDiskTranslationTest()
    : GUITranslationTest("BasicGISAS", "HardDiskBuilder")
{
}

HexParaTranslationTest::HexParaTranslationTest()
    : GUITranslationTest("BasicGISAS", "HexParaCrystalBuilder")
{
}

CoreShellTranslationTest::CoreShellTranslationTest()
    : GUITranslationTest("BasicGISAS", "CoreShellParticleBuilder")
{
}

RoughnessTranslationTest::RoughnessTranslationTest()
    : GUITranslationTest("BasicGISAS", "MultiLayerWithRoughnessBuilder")
{
}

SquareLatticeTranslationTest::SquareLatticeTranslationTest()
    : GUITranslationTest("BasicGISAS", "SquareLatticeBuilder")
{
}

RotationTranslationTest::RotationTranslationTest()
    : GUITranslationTest("BasicGISAS", "RotatedPyramidsBuilder")
{
}

SizeDistributionTranslationTest::SizeDistributionTranslationTest()
    : GUITranslationTest("BasicGISAS", "CylindersWithSizeDistributionBuilder")
{
}

CompositionTranslationTest::CompositionTranslationTest()
    : GUITranslationTest("BasicGISAS", "ParticleCompositionBuilder")
{
}

Para2DTranslationTest::Para2DTranslationTest()
    : GUITranslationTest("BasicGISAS", "Basic2DParaCrystalBuilder")
{
}

Lattice1DTranslationTest::Lattice1DTranslationTest()
    : GUITranslationTest("BasicGISAS", "Lattice1DBuilder")
{
}

Lattice2DTranslationTest::Lattice2DTranslationTest()
    : GUITranslationTest("BasicGISAS", "Basic2DLatticeBuilder")
{
}

TwoLayerRoughnessTranslationTest::TwoLayerRoughnessTranslationTest()
    : GUITranslationTest("BasicGISAS", "TwoLayerRoughnessBuilder")
{
}

MesoCrystalTranslationTest::MesoCrystalTranslationTest()
    : GUITranslationTest("BasicGISAS", "MesoCrystalBuilder")
{
}

MagneticSpheresTranslationTest::MagneticSpheresTranslationTest()
    : GUITranslationTest("BasicPolarizedGISAS", "MagneticSpheresBuilder")
{
}
