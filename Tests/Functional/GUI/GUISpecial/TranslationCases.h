// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/TranslationCases.h
//! @brief     Defines classes from TranslationCases family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISPECIAL_TRANSLATIONCASES_H
#define BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISPECIAL_TRANSLATIONCASES_H

#include "Tests/Functional/GUI/GUISpecial/GUITranslationTest.h"

//! Collection of classes for various translation tests.

class BasicTranslationTest : public GUITranslationTest
{
public:
    BasicTranslationTest();
};

class RadialParaTranslationTest : public GUITranslationTest
{
public:
    RadialParaTranslationTest();
};

class HardDiskTranslationTest : public GUITranslationTest
{
public:
    HardDiskTranslationTest();
};

class HexParaTranslationTest : public GUITranslationTest
{
public:
    HexParaTranslationTest();
};

class CoreShellTranslationTest : public GUITranslationTest
{
public:
    CoreShellTranslationTest();
};

class RoughnessTranslationTest : public GUITranslationTest
{
public:
    RoughnessTranslationTest();
};

class SquareLatticeTranslationTest : public GUITranslationTest
{
public:
    SquareLatticeTranslationTest();
};

class RotationTranslationTest : public GUITranslationTest
{
public:
    RotationTranslationTest();
};

class SizeDistributionTranslationTest : public GUITranslationTest
{
public:
    SizeDistributionTranslationTest();
};

class CompositionTranslationTest : public GUITranslationTest
{
public:
    CompositionTranslationTest();
};

class Para2DTranslationTest : public GUITranslationTest
{
public:
    Para2DTranslationTest();
};

class Lattice1DTranslationTest : public GUITranslationTest
{
public:
    Lattice1DTranslationTest();
};

class Lattice2DTranslationTest : public GUITranslationTest
{
public:
    Lattice2DTranslationTest();
};

class TwoLayerRoughnessTranslationTest : public GUITranslationTest
{
public:
    TwoLayerRoughnessTranslationTest();
};

class MesoCrystalTranslationTest : public GUITranslationTest
{
public:
    MesoCrystalTranslationTest();
};

class MagneticSpheresTranslationTest : public GUITranslationTest
{
public:
    MagneticSpheresTranslationTest();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_GUI_GUISPECIAL_TRANSLATIONCASES_H
