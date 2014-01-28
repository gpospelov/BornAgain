// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/PolarizedDWBAMagCylindersBuilder.h
//! @brief     Defines class PolarizedDWBAMagCylinders1Builder
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef POLARIZEDDWBAMAGCYLINDERSBUILDER_H
#define POLARIZEDDWBAMAGCYLINDERSBUILDER_H

#include "ISampleBuilder.h"

//! @class PolarizedDWBAMagCylinders1Builder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with magnetic material and zero magnetic field.

class BA_CORE_API_ PolarizedDWBAMagCylinders1Builder : public ISampleBuilder
{
public:
    PolarizedDWBAMagCylinders1Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_radius;
    double m_cylinder_height;
};

//! @class PolarizedDWBAMagCylinders2Builder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with magnetic material and non-zero magnetic field.

class BA_CORE_API_ PolarizedDWBAMagCylinders2Builder : public ISampleBuilder
{
public:
    PolarizedDWBAMagCylinders2Builder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_radius;
    double m_cylinder_height;
};


#endif // POLARIZEDDWBAMAGCYLINDERSBUILDER_H
