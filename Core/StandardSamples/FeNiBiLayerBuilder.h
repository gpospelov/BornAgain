// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/FeNiBiLayerBuilder.h
//! @brief     Defines various sample builder classes to
//!            test polarized specular computations
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_FENIBILAYERBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_FENIBILAYERBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

class FeNiBiLayerBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

class FeNiBiLayerTanhBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

class FeNiBiLayerNCBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

class FeNiBiLayerSpinFlipBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

class FeNiBiLayerSpinFlipTanhBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

class FeNiBiLayerSpinFlipNCBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_FENIBILAYERBUILDER_H
