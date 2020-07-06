// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SampleComponents.h
//! @brief     Defines sample components for complex sample builders.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLECOMPONENTS_H
#define SAMPLECOMPONENTS_H

#include "Core/Aggregate/FTDistributions2D.h"
#include "Core/StandardSamples/IRegistry.h"

//! @class FTDistribution2DComponents
//! @brief Predefined Fourier transformed distributions for functional tests.

class FTDistribution2DComponents : public IRegistry<IFTDistribution2D>
{
public:
    FTDistribution2DComponents();
};

//! @class FormFactorComponents
//! @brief Predefined form factors for functional tests.

class FormFactorComponents : public IRegistry<IFormFactor>
{
public:
    FormFactorComponents();
};

#endif // SAMPLECOMPONENTS_H
