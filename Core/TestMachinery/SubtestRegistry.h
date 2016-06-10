// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/SubtestRegistry.h
//! @brief     Declares different registries for subtests of functional tests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTCOMPONENTSREGISTRY_H
#define TESTCOMPONENTSREGISTRY_H

#include "IRegistry.h"
#include "IFormFactor.h"
#include "FTDistributions.h"

// ************************************************************************** //
//! @class TestFTDistribution2DRegistry
//! @brief Registry with predefined Fourier transformed distributions, for functional tests.
// ************************************************************************** //

class TestFTDistribution2DRegistry : public IRegistry<IParameterized>
{
public:
    TestFTDistribution2DRegistry();
};

// ************************************************************************** //
//! @class TestFormFactorsRegistry
//! @brief Registry with predefined form factors, for functional tests.
// ************************************************************************** //

class TestFormFactorsRegistry : public IRegistry<IParameterized>
{
public:
    TestFormFactorsRegistry();
};

#endif // TESTCOMPONENTREGISTRY_H
