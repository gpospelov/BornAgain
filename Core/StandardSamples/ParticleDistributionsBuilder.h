// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/ParticleDistributionsBuilder.h
//! @brief     Defines classes of with different types of particle distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEDISTRIBUTIONSBUILDER_H
#define PARTICLEDISTRIBUTIONSBUILDER_H

#include "ISampleBuilder.h"

//! @class CylindersWithSizeDistributionBuilder
//! @ingroup standard_samples
//! @brief Cylinders in BA with size distributions (IsGISAXS example #3, part II)

class CylindersWithSizeDistributionBuilder : public ISampleBuilder
{
public:
    CylindersWithSizeDistributionBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_height;
    double m_radius;
};



#endif // PARTICLEDISTRIBUTIONSBUILDER_H
