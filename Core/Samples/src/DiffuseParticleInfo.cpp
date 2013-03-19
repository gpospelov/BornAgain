// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/DiffuseParticleInfo.cpp
//! @brief     Implements class DiffuseParticleInfo.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "DiffuseParticleInfo.h"

DiffuseParticleInfo::DiffuseParticleInfo(Particle* p_particle, Geometry::Transform3D *transform, double depth, double abundance)
: ParticleInfo(p_particle, transform, depth, abundance)
, m_number_per_meso(0.0)
{
}

DiffuseParticleInfo::~DiffuseParticleInfo()
{
}
