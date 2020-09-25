// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SlicedCylindersBuilder.h
//! @brief     Defines classes for testing slicing machinery.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDCYLINDERSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDCYLINDERSBUILDER_H

#include "Core/Multilayer/ISampleBuilder.h"

//! Builds sample: cylinders on a silicon substrate
//! @ingroup standard_samples

class SlicedCylindersBuilder : public ISampleBuilder
{
public:
    SlicedCylindersBuilder();
    MultiLayer* buildSample() const override;

protected:
    double m_height;
    double m_radius;
    double m_wavelength;
    unsigned m_n_slices;
};

//! Provides exactly the same sample as SlicedCylindersBuilder, but with
//! sld-based materials. Assumed wavelength is 1.54 Angstrom.
//! @ingroup standard_samples

class SLDSlicedCylindersBuilder : public SlicedCylindersBuilder
{
public:
    SLDSlicedCylindersBuilder();
    MultiLayer* buildSample() const override;
};

//! Provides exactly the same sample as SLDSlicedCylindersBuilder, but with
//! cylinders represented as homogeneous layers. SLD-based materials used.
//! Assumed wavelength is 1.54 Angstrom.
//! @ingroup standard_samples

class AveragedSlicedCylindersBuilder : public SlicedCylindersBuilder
{
public:
    AveragedSlicedCylindersBuilder();
    MultiLayer* buildSample() const override;

private:
    double m_par_surf_density;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_SLICEDCYLINDERSBUILDER_H
