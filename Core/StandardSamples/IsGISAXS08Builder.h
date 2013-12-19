// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS08Builder.h
//! @brief     Defines classes IsGISAXS08ABuilder, IsGISAXS08BBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS08BUILDER_H
#define ISGISAXS08BUILDER_H

#include "ISampleBuilder.h"


//! @class IsGISAXS08ABuilder
//! @ingroup standard_samples
//! @brief Builds sample:  2D paracrystal lattice (IsGISAXS example #8)

class BA_CORE_API_ IsGISAXS08ABuilder : public ISampleBuilder
{
public:
    IsGISAXS08ABuilder();
    ISample *buildSample() const;
};


//! @class IsGISAXS08BBuilder
//! @ingroup standard_samples
//! @brief Builds sample:  2D paracrystal lattice with isotropic pdfs (IsGISAXS example #8)

class IsGISAXS08BBuilder : public ISampleBuilder
{
public:
    IsGISAXS08BBuilder();
    ISample *buildSample() const;
};


#endif // ISGISAXS08BUILDER_H
