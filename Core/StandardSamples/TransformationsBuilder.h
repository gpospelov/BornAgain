// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/TransformationsBuilder.h
//! @brief     Defines classes to build samples with different transformations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMATIONSBUILDER_H
#define TRANSFORMATIONSBUILDER_H

#include "ISampleBuilder.h"

//! @class TransformBoxBuilder
//! @ingroup standard_samples
//! @brief Rotated box in 3 layers system

class BA_CORE_API_ TransformBoxBuilder : public ISampleBuilder
{
public:
    TransformBoxBuilder(){}
    ISample *buildSample() const;
};


#endif // ROTATEDPYRAMIDSBUILDER_H
