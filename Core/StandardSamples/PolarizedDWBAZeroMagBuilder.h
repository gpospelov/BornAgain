// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/PolarizedDWBAZeroMagBuilder.h
//! @brief     Defines class PolarizedDWBAZeroMagBuilder
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef POLARIZEDDWBAZEROMAGBUILDER_H
#define POLARIZEDDWBAZEROMAGBUILDER_H

#include "ISampleBuilder.h"

//! @class PolarizedDWBAZeroMagBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with magnetic material and zero magnetic field.

class BA_CORE_API_ PolarizedDWBAZeroMagBuilder : public ISampleBuilder
{
public:
    PolarizedDWBAZeroMagBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_height;
    double m_cylinder_radius;
};

#endif // ISGISAXS01BUILDER_H
