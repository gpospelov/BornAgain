//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/Particle/SlicedParticle.h
//! @brief     Defines class SlicedParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_PARTICLE_SLICEDPARTICLE_H
#define BORNAGAIN_SAMPLE_PARTICLE_SLICEDPARTICLE_H

#include "Sample/Particle/HomogeneousRegion.h"
#include "Sample/Scattering/IFormFactor.h"
#include <memory>

//! Struct that contains information on a sliced particle.
//! This information is needed for evaluating the sliced form factor and the average of a material,
//! used in the Fresnel calculations.
//!
//! @ingroup intern

struct SlicedParticle {
    std::unique_ptr<IFormFactor> m_slicedff;
    std::vector<HomogeneousRegion> m_regions;
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_SLICEDPARTICLE_H
#endif // USER_API
