//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/FFCompute/IComputeFF.cpp
//! @brief     Implements interface class IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/FFCompute/IComputeFF.h"

IComputeFF::IComputeFF(const IFormFactor& ff)
    : m_ff(ff.clone())
{
}

void IComputeFF::setAmbientMaterial(const Material& material)
{
    m_ff->setAmbientMaterial(material);
}

double IComputeFF::volume() const
{
    return m_ff->volume();
}

double IComputeFF::radialExtension() const
{
    return m_ff->radialExtension();
}

double IComputeFF::bottomZ(const IRotation& rotation) const
{
    return m_ff->bottomZ(rotation);
}

double IComputeFF::topZ(const IRotation& rotation) const
{
    return m_ff->topZ(rotation);
}
