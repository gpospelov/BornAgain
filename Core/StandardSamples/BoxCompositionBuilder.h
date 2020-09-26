// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/BoxCompositionBuilder.h
//! @brief     Defines classes of BoxCompositionBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_BOXCOMPOSITIONBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_BOXCOMPOSITIONBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

class MultiLayer;
class ParticleComposition;

//! Parent class to test all kind of compositions made out of boxes.
//! Reproduces Python functional test transform_BoxComposition.py
//! @ingroup standard_samples

class BoxCompositionBuilder : public ISampleBuilder
{
protected:
    MultiLayer* createMultiLayer(const ParticleComposition& composition) const;
};

//! Two boxes in particle composition rotated in X by 90 degrees.
//! @ingroup standard_samples

class BoxCompositionRotateXBuilder : public BoxCompositionBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! Two boxes in particle composition rotated in Y by 90 degrees.
//! @ingroup standard_samples

class BoxCompositionRotateYBuilder : public BoxCompositionBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! Two boxes in particle composition rotated in Z by 90 degrees.
//! @ingroup standard_samples

class BoxCompositionRotateZBuilder : public BoxCompositionBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! Two boxes in particle composition rotated in Z and Y by 90 degrees.
//! @ingroup standard_samples

class BoxCompositionRotateZandYBuilder : public BoxCompositionBuilder
{
public:
    MultiLayer* buildSample() const;
};

//! Two different boxes are first rotated and then composed, composition is then rotated.
//! @ingroup standard_samples

class BoxStackCompositionBuilder : public BoxCompositionBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_BOXCOMPOSITIONBUILDER_H
