// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/SubtestRegistry.h
//! @brief     Defines different registries for subtests of functional tests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SUBTESTREGISTRY_H
#define SUBTESTREGISTRY_H

#include "IRegistry.h"
#include "FTDistributions2D.h"

class ISubtestRegistry : public IRegistry<IParameterized>
{
};

// ************************************************************************** //
//! @class SubtestRegistryFTDistribution2D
//! @brief Registry with predefined Fourier transformed distributions, for functional tests.
// ************************************************************************** //

class SubtestRegistryFTDistribution2D : public IRegistry<IFTDistribution2D>
{
public:
    SubtestRegistryFTDistribution2D();
};

// ************************************************************************** //
//! @class SubtestRegistryFormFactor
//! @brief Registry with predefined form factors, for functional tests.
// ************************************************************************** //

class SubtestRegistryFormFactor : public ISubtestRegistry
{
public:
    SubtestRegistryFormFactor();
};

#endif // SUBTESTREGISTRY_H
