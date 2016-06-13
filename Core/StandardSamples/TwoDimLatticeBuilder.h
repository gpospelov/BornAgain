// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TwoDimLatticeBuilder.h
//! @brief     Declares class IsGISAXS06Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS06BUILDER_H
#define ISGISAXS06BUILDER_H

#include "ISampleBuilder.h"


//! @class SquareLatticeBuilder
//! @ingroup standard_samples
//! @brief Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

class BA_CORE_API_ SquareLatticeBuilder : public ISampleBuilder
{
public:
    SquareLatticeBuilder(){}
    ISample *buildSample() const;
};


//! @class CenteredSquareLatticeBuilder
//! @ingroup standard_samples
//! @brief Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

class BA_CORE_API_ CenteredSquareLatticeBuilder : public ISampleBuilder
{
public:
    CenteredSquareLatticeBuilder(){}
    ISample *buildSample() const;
};

//! @class RotatedSquareLatticeBuilder
//! @ingroup standard_samples
//! @brief Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

class BA_CORE_API_ RotatedSquareLatticeBuilder : public ISampleBuilder
{
public:
    RotatedSquareLatticeBuilder(){}
    ISample *buildSample() const;
};

#endif // ISGISAXS06BUILDER_H
