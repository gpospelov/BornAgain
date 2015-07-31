// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/TestComponentsRegistry.h
//! @brief     Defines different registries for functional test component service.
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

#include "ICloneableRegistry.h"
#include "IFormFactor.h"
#include "FTDistributions.h"

//! @class TestFTDistribution2DRegistry
//! @ingroup standard_samples
//! @brief Registry with predifined fourier transformed distributions for functional tests purpose.

class TestFTDistribution2DRegistry : public ICloneableRegistry<std::string, IFTDistribution2D>
{
public:
    TestFTDistribution2DRegistry();
};


//! @class TestFormFactorsRegistry
//! @ingroup standard_samples
//! @brief Registry with predifined form factors for functional tests purpose.

class TestFormFactorsRegistry : public ICloneableRegistry<std::string, IFormFactor>
{
public:
    TestFormFactorsRegistry();
};

#endif // TESTCOMPONENTREGISTRY_H
