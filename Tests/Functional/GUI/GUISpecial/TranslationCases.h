// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/TranslationCases.h
//! @brief     Defines classes from TranslationCases family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSLATIONCASES_H
#define TRANSLATIONCASES_H

#include "GUITranslationTest.h"

//! Collection of classes for various translation tests.

class BasicTranslationTest : public GUITranslationTest
{
public:
    BasicTranslationTest();
    ~BasicTranslationTest();
};

class RadialParaTranslationTest : public GUITranslationTest
{
public:
    RadialParaTranslationTest();
    ~RadialParaTranslationTest();
};

class HexParaTranslationTest : public GUITranslationTest
{
public:
    HexParaTranslationTest();
    ~HexParaTranslationTest();
};

class CoreShellTranslationTest : public GUITranslationTest
{
public:
    CoreShellTranslationTest();
    ~CoreShellTranslationTest();
};

class RoughnessTranslationTest : public GUITranslationTest
{
public:
    RoughnessTranslationTest();
    ~RoughnessTranslationTest();
};

class SquareLatticeTranslationTest : public GUITranslationTest
{
public:
    SquareLatticeTranslationTest();
    ~SquareLatticeTranslationTest();
};

class RotationTranslationTest : public GUITranslationTest
{
public:
    RotationTranslationTest();
    ~RotationTranslationTest();
};

class SizeDistributionTranslationTest : public GUITranslationTest
{
public:
    SizeDistributionTranslationTest();
    ~SizeDistributionTranslationTest();
};

class CompositionTranslationTest : public GUITranslationTest
{
public:
    CompositionTranslationTest();
    ~CompositionTranslationTest();
};

class Para2DTranslationTest : public GUITranslationTest
{
public:
    Para2DTranslationTest();
    ~Para2DTranslationTest();
};

class Lattice1DTranslationTest : public GUITranslationTest
{
public:
    Lattice1DTranslationTest();
    ~Lattice1DTranslationTest();
};

class Lattice2DTranslationTest : public GUITranslationTest
{
public:
    Lattice2DTranslationTest();
    ~Lattice2DTranslationTest();
};

class TwoLayerRoughnessTranslationTest : public GUITranslationTest
{
public:
    TwoLayerRoughnessTranslationTest();
    ~TwoLayerRoughnessTranslationTest();
};

class MesoCrystalTranslationTest : public GUITranslationTest
{
public:
    MesoCrystalTranslationTest();
    ~MesoCrystalTranslationTest();
};

class MagneticSpheresTranslationTest : public GUITranslationTest
{
public:
    MagneticSpheresTranslationTest();
    ~MagneticSpheresTranslationTest();
};

#endif // TRANSLATIONCASES_H
