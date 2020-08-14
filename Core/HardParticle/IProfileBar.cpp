// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/IProfileBar.cpp
//! @brief     Implements class ProfileBar.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/IProfileBar.h"
#include "Core/HardParticle/Ripples.h"
#include "Core/Shapes/Box.h" // from Shapes/

IProfileBar::IProfileBar(const NodeMeta& meta, const std::vector<double>& PValues)
    : IFormFactorBorn(nodeMetaUnion({{"Length", "nm", "Length", 0, INF, 1.},
                           {"Width", "nm", "Width", 0, INF, 1.},
                           {"Height", "nm", "Height", 0, INF, 1.}},
            meta),
            PValues),
      m_length(m_P[0]), m_width(m_P[1]), m_height(m_P[2])
{
}

double IProfileBar::radialExtension() const
{
    return (m_width + m_length) / 4.0;
}

//! Complex form factor.
complex_t IProfileBar::factor_yz(complex_t qy, complex_t qz) const
{
    return ripples::profile_yz_bar(qy, qz, m_width, m_height);
}

void IProfileBar::onChange()
{
    mP_shape.reset(new Box(m_length, m_width, m_height));
}
