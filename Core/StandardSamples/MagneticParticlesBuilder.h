// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/PolarizedParticlesBuilder.h
//! @brief     Declares class to build magnetic samples
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MAGNETICPARTICLESBUILDER_H
#define MAGNETICPARTICLESBUILDER_H

#include "ISampleBuilder.h"

//! @class MagneticParticleZeroFieldBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with magnetic material and zero magnetic field.

class BA_CORE_API_ MagneticParticleZeroFieldBuilder : public ISampleBuilder
{
public:
    MagneticParticleZeroFieldBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_radius;
    double m_cylinder_height;
};

//! @class MagneticCylindersBuilder
//! @ingroup standard_samples
//! @brief Builds sample: cylinders with magnetic material and non-zero magnetic field.

class BA_CORE_API_ MagneticCylindersBuilder : public ISampleBuilder
{
public:
    MagneticCylindersBuilder();
    ISample *buildSample() const;

protected:
    void init_parameters();

private:
    double m_cylinder_radius;
    double m_cylinder_height;
};


#endif // MAGNETICPARTICLESBUILDER_H
