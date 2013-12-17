// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS10Builder.h
//! @brief     Defines class IsGISAXS10Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS10BUILDER_H
#define ISGISAXS10BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS10Builder class to build sample: cylinders on top of substrate
//! with interference (IsGISAXS example #10)
class IsGISAXS10Builder : public ISampleBuilder
{
public:
    IsGISAXS10Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_height;
    double m_cylinder_radius;
};

#endif // ISGISAXS10BUILDER_H
